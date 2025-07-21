#include "muser.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include "../repo/mrepo.h"

using json = nlohmann::json;

bool AppModels::User::login(AppModels::User & user, const std::string& token) {
    try {
        
        cpr::Response res = cpr::Get(
            cpr::Url{"https://api.github.com/user"},
            cpr::Header{
                {"Authorization", "token " + token},
                {"User-Agent", "git_air"}
            }
        );

        // check for http error
        if (res.status_code != 200) {
            // code for error handling
            return false;
        }

        // json response
        json json_res = json::parse(res.text);
        
        user.setUsername(json_res["login"].get<std::string>());
        user.setName(json_res.value("name", ""));
        user.setToken(token);
        user.setEmail(json_res.value("email", ""));

    } catch (const std::exception &e) {
        // some error handling code
        // std::cerr << "Exception: " << e.what() << std::endl;
    }

    return true;

}

bool AppModels::User::fetchUserRepos(){
    try {
        int page = 1;
        repos.clear();
        while (true) {
            std::string url = "https://api.github.com/user/repos?sort=updated&page=" + std::to_string(page);

            cpr::Response res = cpr::Get(
                cpr::Url{url},
                cpr::Header{
                    {"Authorization", "token " + getToken()},
                    {"User-Agent", "git_air"}
                }
            );

            if (res.status_code != 200) {
                // some error code
                return false;
            }

            json json_res = json::parse(res.text);

            if (json_res.empty()) {
                break; // No more repos, exit loop
            }

            for (const auto &repo_json : json_res) {
                AppModels::Repo repo;
                repo.name        = repo_json["name"].get<std::string>();
                repo.full_name   = repo_json["full_name"].get<std::string>();
                if (repo_json["description"].is_null()) {
                    repo.description = "(No description)";
                } else {
                    repo.description = repo_json["description"].get<std::string>();
                }
                
                repo.privateRepo = repo_json["private"].get<bool>();
                repo.html_url    = repo_json["html_url"].get<std::string>();

                repos.push_back(repo);
            }

            page++; // Move to next page
        }
        return true;
    } catch(const std::exception &e) {
        // error page
        return false;
    }
}

std::vector<AppModels::Repo> AppModels::User::loadRepos(){
    return repos;
}
