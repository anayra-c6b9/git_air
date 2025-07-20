#ifndef MUSER_H
#define MUSER_H

#include "../repo/mrepo.h"

#include <string>

namespace AppModels {

    class User {
        private:
            std::string username;
            std::string email;
            std::string name;
            std::string token; // GitHub Personal Access Token

        public:
            // Setters
            void setUsername(const std::string& uname) { username = uname; }
            void setEmail(const std::string& mail) { email = mail; }
            void setName(const std::string& nm) { name = nm; }
            void setToken(const std::string& t) { token = t; }
            
            // Getters
            std::string getUsername() const { return username; }
            std::string getEmail() const { return email; }
            std::string getName() const { return name; }
            std::string getToken() const { return token; }

            // ops
            static bool login(AppModels::User& user, const std::string& token);
            static bool fetchUserRepos(AppModels::User& user, std::vector<AppModels::Repo> &repos);
            void clearValues(){
                setUsername("");
                setEmail("");
                setName("");
                setToken("");
            }
    };

}

#endif
