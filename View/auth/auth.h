#ifndef AUTH_H
#define AUTH_H

#include <string>

using uint = unsigned int;

namespace AuthNS{
	
	class AuthWindow{
		private:
			static uint window_number;
			static uint window_created;
			uint id;
			bool is_active = false;
			std::string email;
			std::string username;
			std::string passkey;
			bool is_user_saved = false;
		public:
			AuthWindow() {
				window_number++;
				id = ++window_created;
				is_active = true;
			}

			void setEmail(std::string email);
			std::string getEmail();
			void setUsername(std::string username);
			std::string getUsername();
			void setPasskey(std::string passkey);
			std::string getPasskey();
			void toggleIsUserSaved();
			bool getIsUserSaved();
			bool login();

			~AuthWindow(){
				is_active = false;
				window_number--;
			}
	};

}

#endif
