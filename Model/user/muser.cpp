#include "muser.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

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

bool AppModels::User::fetchUserRepos(AppModels::User & user, std::vector<AppModels::Repo> &repos){
    try {
        // API call to fetch repositories
        cpr::Response res = cpr::Get(
            cpr::Url{"https://api.github.com/user/repos"},
            cpr::Header{
                {"Authorization", "token " + user.getToken()},
                {"User-Agent", "git_air"}
            }
        );

        // Check for HTTP error
        if (res.status_code != 200) {
            // error code
            return false;
        }

        // Parse JSON array
        json json_res = json::parse(res.text);

        for (const auto &repo_json : json_res) {
            AppModels::Repo repo;

            repo.name        = repo_json["name"].get<std::string>();
            repo.full_name   = repo_json["full_name"].get<std::string>();
            repo.description = repo_json.value("description", "");
            repo.privateRepo = repo_json["private"].get<bool>();
            repo.html_url    = repo_json["html_url"].get<std::string>();

            repos.push_back(repo);
        }

        return true;
    } catch (const std::exception &e) {
        // some error code
    }

    return false;
}

