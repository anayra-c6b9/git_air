#ifndef CLONE_REPO_H
#define CLONE_REPO_H

#include <string>

#include "../../components/page/page.h"
#include "../auth/auth.h"

using uint = unsigned int;

namespace AppPages{
	
	class CloneRepoPage: public AppComponent::Page{
		private:
            uint current_selection;
            AppPages::authData page_data[2];
            std::string link;
            std::string path;
			enum Field {
                LINK = 0,
                PATH = 1,
                CLONE = 2,
				TOTAL_FIELDS = 3
			};
		public:
			CloneRepoPage() {
				current_selection = 0;
				hasFooter = true;
                path = "";
                link = "";
                page_data[0] = {1, "Enter Repository Link"};
                page_data[1] = {2, "Enter Local path for the repository"};
			}

			void display() override;
            void handleInput(int ch, AppComponent::App *app) override ;
            bool clone();
			~CloneRepoPage(){
			}
	};

}

#endif
