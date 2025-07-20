#ifndef HOME_H
#define HOME_H

#include <string>
#include "../../components/page/page.h"
// #include "../../../Model/user/muser.h"
// #include "../../components/app/app.h"

using uint = unsigned int;

namespace AppPages{

    struct pageElement
	{
		uint id;
		std::string label;
        std::string navigate_to;
	};
	
	class HomePage: public AppComponent::Page{
		private:
            uint current_selection;
            AppPages::pageElement page_element[3];
			bool is_user_saved = false;
			enum Field {
				field1 = 0,
				field2 = 1,
				field3 = 2,
				TOTAL_FIELDS = 3
			};
		public:
			HomePage() {
				current_selection = 0;
				hasFooter = true;
				// username
				page_element[0] = {1, "Select Local repository", "browse"};
				page_element[1] = {2, "View all github repository", ""};
				page_element[2] = {3, "Clone remote repository", "clone_repo"};
			}

			void display() override;
            void handleInput(int ch, AppComponent::App *app) override ;

			~HomePage(){
			}
	};

}

#endif
