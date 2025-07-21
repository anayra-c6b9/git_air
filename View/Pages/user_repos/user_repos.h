#ifndef USER_REPOS_H
#define USER_REPOS_H

#include <string>

#include "../../components/page/page.h"
#include "../auth/auth.h"
#include "../../../Model/repo/mrepo.h"
#include "../../../Model/user/muser.h"
#include "../../../all_globals.h"

using uint = unsigned int;

namespace AppPages{
	
	class UserReposPage: public AppComponent::Page{
		private:
            uint current_selection;
            uint last_selection;
            uint view_item_freq;
            uint starting_point;
            uint ending_point;
            std::vector<AppModels::Repo> user_repos;
		public:
            bool hasRepos;
			UserReposPage() {
				current_selection = 0;
                last_selection = 0;
				hasFooter = true;
                view_item_freq = 0;
                starting_point = 0;
                ending_point = 0;
			}
            void loadUserRepos(AppModels::User &user) {
                user_repos.clear(); // clear any old data
                user_repos = user.loadRepos();
            }

			void display() override;
            void handleInput(int ch, AppComponent::App *app) override ;
			void clearValues() override;
            void setViewItemFrequency(uint upper_limit, uint lower_limit);
			~UserReposPage(){
			}
	};

}

#endif