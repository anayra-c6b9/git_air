#ifndef BROWSE_H
#define BROWSE_H

#include <string>

#include "../../components/page/page.h"

using uint = unsigned int;

namespace AppPages{
	
	class BrowsePage: public AppComponent::Page{
		private:
            uint current_selection;
            std::string path;
			bool is_valid_repo;
			bool is_checked;
			enum Field {
                PATH = 0,
                BROWSE = 1,
				TOTAL_FIELDS = 2
			};
		public:
			BrowsePage() {
				current_selection = 0;
				hasFooter = true;
                path = "";
				is_valid_repo = false;
				is_checked = false;
			}

			void display() override;
            void handleInput(int ch, AppComponent::App *app) override ;
            bool browse();
			void clearValues() override;
			bool checkGitRepository();
			~BrowsePage(){
			}
	};

}

#endif
