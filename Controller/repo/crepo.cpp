#include "crepo.h"
#include "../../all_globals.h"
#include "../../Model/repo/mrepo.h"
#include "../../Model/user/muser.h"
#include <string>

std::vector<AppModels::Repo> AppControllers::Repo::fetchUserRepos(){
    std::vector<AppModels::Repo> all_repos;

    AppModels::User::fetchUserRepos(user, all_repos);

    return all_repos;
}


