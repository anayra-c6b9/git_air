#ifndef CREPO_H
#define CREPO_H


#include "../../Model/repo/mrepo.h"

#include <string>

namespace AppControllers {

    // bool login(AppModels::User& user, const std::string& token);

    class Repo {
        public:
            static std::vector<AppModels::Repo> fetchUserRepos();
    };
}

#endif
