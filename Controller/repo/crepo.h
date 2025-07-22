#ifndef CREPO_H
#define CREPO_H


#include "../../Model/repo/mrepo.h"
#include "../../Model/local_repo/mlocal_repo.h"

#include <string>

namespace AppControllers {

    // bool login(AppModels::User& user, const std::string& token);

    class Repo {
        public:
            static std::vector<AppModels::Repo> fetchUserRepos();
            static bool isGitRepo(const std::string path);
            static AppModels::LocalRepo * getRepoInfo(const std::string path);
            static bool pushRepo(std::string token);
    };
}

#endif
