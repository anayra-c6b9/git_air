#include "../../all_globals.h"
#include "cauth.h"
#include "../../Model/user/muser.h"
#include <string>
/**
 * Fetches the authenticated user’s profile and populates @p user.
 * @return true  on success (HTTP 200) | false otherwise.
 */

bool AppControllers::Auth::login(std::string &token) {
    try {
        if(AppModels::User::login(user, token)){
            // success
            return true;
        }

    } catch (const std::exception &e) {
        // some error handling code
        // std::cerr << "Exception: " << e.what() << std::endl;
    }

    return false;

}