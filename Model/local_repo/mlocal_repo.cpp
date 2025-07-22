#include "mlocal_repo.h"
#include <git2.h>

bool AppModels::LocalRepo::checkIfGitRepo(const std::string path){
    git_repository* repo = nullptr;
    bool hasRemote = false;

    // Initialize libgit2
    git_libgit2_init();

    // Try to open the repo at given path
    if (git_repository_open(&repo, path.c_str()) == 0) {
        // Get list of remotes
        git_strarray remotes = {0};
        if (git_remote_list(&remotes, repo) == 0) {
            if (remotes.count > 0) {
                hasRemote = true;
            }
            git_strarray_dispose(&remotes);
        }
        git_repository_free(repo);
    }

    git_libgit2_shutdown();
    return hasRemote;
}

void AppModels::LocalRepo::extractRepoInfo(){
    git_repository* repo = nullptr;

    git_libgit2_init();

    if (git_repository_open(&repo, repo_path.c_str()) == 0) {
        // Repo name from path
        size_t lastSlash = repo_path.find_last_of("/\\");
        repo_name = (lastSlash == std::string::npos) ? repo_path : repo_path.substr(lastSlash + 1);

        // Default branch
        git_reference* head = nullptr;
        if (git_repository_head(&head, repo) == 0 && git_reference_is_branch(head)) {
            const char* branchName = nullptr;
            git_branch_name(&branchName, head);
            if (branchName) {
                default_branch = branchName;
            }
            git_reference_free(head);
        } else {
            default_branch = "(detached HEAD)";
        }

        // Remote URLs
        git_strarray remotes = {0};
        if (git_remote_list(&remotes, repo) == 0) {
            for (size_t i = 0; i < remotes.count; ++i) {
                git_remote* remote = nullptr;
                if (git_remote_lookup(&remote, repo, remotes.strings[i]) == 0) {
                    repo_remotes.push_back(git_remote_url(remote));
                    git_remote_free(remote);
                }
            }
            git_strarray_dispose(&remotes);
        }

        git_repository_free(repo);
    }

    git_libgit2_shutdown();
}

static int credentials_callback(git_credential **out,
                         const char *url,
                         const char *username_from_url,
                         unsigned int allowed_types,
                         void *payload) {
    git_cred *cred = nullptr;
    std::string token = *static_cast<std::string *>(payload);
    // GitHub expects username as "x-access-token" and token as password
    return git_cred_userpass_plaintext_new(&cred, "x-access-token", token.c_str());
}

bool AppModels::LocalRepo::pushToOriginMainWithToken(const std::string& github_token) {
    git_libgit2_init();

    git_repository* repo = nullptr;
    git_remote* remote = nullptr;

    // Open the local repo
    int error = git_repository_open(&repo, repo_path.c_str());
    if (error < 0) {
        git_repository_free(repo);
        git_libgit2_shutdown();
        return false;
    }

    // Lookup remote "origin"
    error = git_remote_lookup(&remote, repo, "origin");
    if (error < 0) {
        git_repository_free(repo);
        git_libgit2_shutdown();
        return false;
    }

    // Set up push options with HTTPS token
    git_push_options push_opts;
    git_push_options_init(&push_opts, GIT_PUSH_OPTIONS_VERSION);

    // Create a copy of the token
    std::string* token_copy = new std::string(github_token);

    // Set up credentials callback
    push_opts.callbacks.credentials = [](git_credential** out,
                                         const char* url,
                                         const char* username_from_url,
                                         unsigned int allowed_types,
                                         void* payload) -> int {
        auto* token = static_cast<std::string*>(payload);
        return git_credential_userpass_plaintext_new(out,
                                                     "x-access-token",
                                                     token->c_str());
    };
    push_opts.callbacks.payload = token_copy;

    // Refspec for pushing main
    const char* refspecs[] = {"refs/heads/main"};
    git_strarray refspec_array = {const_cast<char**>(refspecs), 1};

    // Push
    error = git_remote_push(remote, &refspec_array, &push_opts);

    // Cleanup
    delete token_copy;
    git_remote_free(remote);
    git_repository_free(repo);
    git_libgit2_shutdown();

    if (error < 0) {
        return false;
    }

    return true;
}

bool AppModels::LocalRepo::commitAndPushAll(const std::string& message, const std::string& github_token) {
    git_libgit2_init();

    git_repository* repo = nullptr;
    git_index* index = nullptr;
    git_oid tree_id, commit_id;
    git_signature* sig = nullptr;
    git_tree* tree = nullptr;
    git_remote* remote = nullptr;

    // Open repo
    if (git_repository_open(&repo, repo_path.c_str()) != 0) {
        git_libgit2_shutdown();
        return false;
    }

    // Set up signature (use repo config if available)
    if (git_signature_default(&sig, repo) != 0) {
        git_signature_now(&sig, "Your Name", "you@example.com"); // fallback
    }

    // Add all changes (equivalent to `git add .`)
    if (git_repository_index(&index, repo) != 0) {
        git_repository_free(repo);
        git_libgit2_shutdown();
        return false;
    }
    if (git_index_add_all(index, nullptr, GIT_INDEX_ADD_DEFAULT, nullptr, nullptr) != 0) {
        git_index_free(index);
        git_repository_free(repo);
        git_libgit2_shutdown();
        return false;
    }
    if (git_index_write(index) != 0) {
        git_index_free(index);
        git_repository_free(repo);
        git_libgit2_shutdown();
        return false;
    }

    // Write tree object
    if (git_index_write_tree(&tree_id, index) != 0) {
        git_index_free(index);
        git_repository_free(repo);
        git_libgit2_shutdown();
        return false;
    }

    if (git_tree_lookup(&tree, repo, &tree_id) != 0) {
        git_tree_free(tree);
        git_index_free(index);
        git_repository_free(repo);
        git_libgit2_shutdown();
        return false;
    }

    // Get current HEAD to use as parent
    git_reference* head_ref = nullptr;
    git_commit* parent_commit = nullptr;
    if (git_repository_head(&head_ref, repo) == 0) {
        if (git_commit_lookup(&parent_commit, repo, git_reference_target(head_ref)) != 0) {
            // Ignore if no parent (e.g., first commit)
            parent_commit = nullptr;
        }
    }

    // Commit (equivalent to `git commit -m "message"`)
    if (git_commit_create_v(&commit_id,
                            repo,
                            "HEAD",
                            sig,
                            sig,
                            nullptr,
                            message.c_str(),
                            tree,
                            parent_commit ? 1 : 0,
                            parent_commit) != 0) {
        git_tree_free(tree);
        git_index_free(index);
        git_repository_free(repo);
        git_libgit2_shutdown();
        return false;
    }

    git_index_free(index);
    git_tree_free(tree);
    if (parent_commit) git_commit_free(parent_commit);
    if (head_ref) git_reference_free(head_ref);
    git_signature_free(sig);

    // Push (equivalent to `git push origin main`)
    if (git_remote_lookup(&remote, repo, "origin") != 0) {
        git_repository_free(repo);
        git_libgit2_shutdown();
        return false;
    }

    git_push_options push_opts;
    git_push_options_init(&push_opts, GIT_PUSH_OPTIONS_VERSION);

    std::string* token_copy = new std::string(github_token);
    push_opts.callbacks.credentials = [](git_credential** out,
                                         const char* url,
                                         const char* username_from_url,
                                         unsigned int allowed_types,
                                         void* payload) -> int {
        auto* token = static_cast<std::string*>(payload);
        return git_credential_userpass_plaintext_new(out,
                                                     "x-access-token",
                                                     token->c_str());
    };
    push_opts.callbacks.payload = token_copy;

    const char* refspecs[] = {"refs/heads/main"};
    git_strarray refspec_array = {const_cast<char**>(refspecs), 1};

    if (git_remote_push(remote, &refspec_array, &push_opts) != 0) {
        delete token_copy;
        git_remote_free(remote);
        git_repository_free(repo);
        git_libgit2_shutdown();
        return false;
    }

    delete token_copy;
    git_remote_free(remote);
    git_repository_free(repo);
    git_libgit2_shutdown();
    return true;
}
