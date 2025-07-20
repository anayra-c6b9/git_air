#ifndef CAUTH_H
#define CAUTH_H

#include "../../Model/user/muser.h"
#include <string>

namespace AppControllers {

    // bool login(AppModels::User& user, const std::string& token);

    class Auth {
        public:
            static bool login(std::string &token);
    };
}

#endif
