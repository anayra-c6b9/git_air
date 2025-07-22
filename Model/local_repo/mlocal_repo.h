#ifndef MLOCAL_REPO_H
#define MLOCAL_REPO_H

#include <string>

namespace AppModels {
    class LocalRepo {
        public:
            std::string repo_path;
            std::string repo_name;
            std::vector<std::string> repo_remotes;
            std::string default_branch;

            LocalRepo(std::string path): repo_path(path){};
            static bool checkIfGitRepo(const std::string str);
            void extractRepoInfo();
            bool pushToOriginMainWithToken(const std::string& github_token);
            bool commitAndPushAll(const std::string& message, const std::string& github_token);
    };
}

#endif