#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "../../components/page/page.h"
#include "../../../Model/user/muser.h"
// #include "../../components/app/app.h"

using uint = unsigned int;

namespace AppPages{


	struct authData
	{
		uint id;
		std::string label;
	};
	
	
	class AuthPage: public AppComponent::Page{
		private:
			uint current_selection;
			uint id;
			bool is_active = false;
			std::string email;
			std::string username;
			std::string passkey;
			authData auth_data[3];
			bool is_user_saved = false;
			enum Field {
				USERNAME = 0,
				EMAIL = 1,
				PASSKEY = 2,
				LOGIN = 3,
				TOTAL_FIELDS = 4
			};
		public:
			AuthPage() {
				is_active = true;
				current_selection = 0;
				hasFooter = true;
				// username
				auth_data[0] = {1, "Username"};
				auth_data[1] = {2, "Email"};
				auth_data[2] = {3, "Github Token"};
			}

			void setEmail(std::string email);
			std::string getEmail();
			void setUsername(std::string username);
			std::string getUsername();
			void setPasskey(std::string passkey);
			std::string getPasskey();
			void toggleIsUserSaved();
			bool getIsUserSaved();
			void display() override;
            void handleInput(int ch, AppComponent::App *app) override ;
			bool login();
			void clearValues() override;

			~AuthPage(){
				is_active = false;
			}
	};

}

#endif
