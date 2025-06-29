#ifndef AUTH_H
#define AUTH_H

#include <string>

using uint = unsigned int;

namespace AuthNS{


	struct authData
	{
		uint id;
		// uint label_y;
		// uint label_;
		std::string label;
		// uint input_y;
		// uint input_x;
		// std::string input;
		// uint input_length;
	};
	
	
	class AuthWindow{
		private:
			static uint window_number;
			static uint window_created;
			uint current_selection;
			uint id;
			bool is_active = false;
			std::string email;
			std::string username;
			std::string passkey;
			authData auth_data[3];
			bool is_user_saved = false;
		public:
			AuthWindow() {
				window_number++;
				id = ++window_created;
				is_active = true;
				current_selection = -1;

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
			void displayAuthPage();
			bool login();

			~AuthWindow(){
				is_active = false;
				window_number--;
			}
	};

}

#endif
