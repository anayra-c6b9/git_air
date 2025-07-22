#include "crepo.h"
#include "../../all_globals.h"
#include "../../Model/repo/mrepo.h"
#include "../../Model/user/muser.h"
#include "../../Model/local_repo/mlocal_repo.h"
#include <string>

std::vector<AppModels::Repo> AppControllers::Repo::fetchUserRepos(){
    std::vector<AppModels::Repo> all_repos;

    user.fetchUserRepos();
    all_repos = user.loadRepos();

    return all_repos;
}

bool AppControllers::Repo::isGitRepo(const std::string path){
    return AppModels::LocalRepo::checkIfGitRepo(path);
}

AppModels::LocalRepo * AppControllers::Repo::getRepoInfo(const std::string path){
    AppModels::LocalRepo* repo = new AppModels::LocalRepo(path);

    repo->extractRepoInfo();

    return repo;
}

bool AppControllers::Repo::pushRepo(std::string token){
    return false;
};
