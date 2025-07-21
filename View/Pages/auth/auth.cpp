#include "auth.h"
#include <string>
#include <ncurses.h>
#include "../../globals.h"
#include "../../components/text_with_label/text_with_label.h"
#include "../../components/app/app.h"
#include "../../components/button_with_label/button_with_label.h"

#include "../../../Model/user/muser.h"
#include "../../../Controller/auth/cauth.h"
#include "../../../all_globals.h"
#include "../../../Controller/repo/crepo.h"

using uint = unsigned int;

void AppPages::AuthPage::setEmail(std::string email) {
	this->email = email;
}

std::string AppPages::AuthPage::getEmail() {
	return email;
}

void AppPages::AuthPage::setUsername(std::string username) {
	this->username = username;
}

std::string AppPages::AuthPage::getUsername() {
	return username;
}

void AppPages::AuthPage::setPasskey(std::string passkey) {
	this->passkey = passkey;
}

std::string AppPages::AuthPage::getPasskey() {
	return passkey;
}

void AppPages::AuthPage::toggleIsUserSaved() {
	is_user_saved = !is_user_saved;
}

bool AppPages::AuthPage::getIsUserSaved() {
	return is_user_saved;
}

static int getExtraSpace(int winSize, int len) {
		int extra_length = winSize - len > 0 ? winSize - len : 0;
		return extra_length;
}

static int getLesser(int param1, int param2) {
		return param1 < param2 ? param1 : param2;
}

void AppPages::AuthPage::display(){
    int lower_limit,
		extraSpace = 0,
		title_length = 26,
		margin = 0,
		iter_y = 4,
		iter_x = 1;

		extraSpace = getExtraSpace(app_win.getAppWinWidth(), title_length);
		lower_limit = extraSpace/2;

		mvaddstr(0, lower_limit, "┌");
		for(int i = 0; i < title_length - 2; i++)
				mvaddstr(0, lower_limit+1+i, "─");
		mvaddstr(0, lower_limit + title_length - 1, "┐");
		// mvaddwstr(2, lower_limit, L"\u2503 ADD GITHUB CREDENTIALS \u2503");
		mvaddstr(1, lower_limit, "┃ ADD GITHUB CREDENTIALS ┃");
		// if(title_length - 3 <= app_win.getAppWinWidth()){
		// }
		mvaddstr(2, lower_limit, "└");
		for(int i = 0; i < title_length-2; i++)
				mvaddstr(2, lower_limit+1+i, "─");
		mvaddstr(2, lower_limit + title_length - 1, "┘");

		// UI

		// creating a button object
		std::string button_label_name = "LOG IN";
		AppComponent::ButtonWithLabel button(3 /*height*/, button_label_name.length() + 2, button_label_name);

		AppComponent::stringInputComponent(auth_data[0].id, auth_data[0].label, username, current_selection == USERNAME, iter_y + 0*3, iter_x);
		AppComponent::stringInputComponent(auth_data[1].id, auth_data[1].label, email, current_selection == EMAIL, iter_y + 1*3, iter_x);
		AppComponent::stringInputComponent(auth_data[2].id, auth_data[2].label, passkey, current_selection == PASSKEY, iter_y + 2*3, iter_x);
		
		extraSpace = getExtraSpace(app_win.getAppWinWidth(), button_label_name.length());
		lower_limit = extraSpace/2;
		button.display(iter_y + 3*3, lower_limit, current_selection == LOGIN);

}

void AppPages::AuthPage::handleInput(int ch, AppComponent::App *app) {
	if(app->isEscapeMode()){
		app->handleModeKey(ch);
		return;
	}
	switch (ch) {
		case KEY_ESC:
			app->toggleMode();
			break;
        case KEY_UP:
            if (current_selection > 0)
                current_selection--;
            break;
        case KEY_DOWN:
            if (current_selection < TOTAL_FIELDS - 1)
                current_selection++;
            break;
        case KEY_BACKSPACE:
        case 127: // MacOS backspace
            if (current_selection == USERNAME && !username.empty())
                username.pop_back();
            else if (current_selection == EMAIL && !email.empty())
                email.pop_back();
            else if (current_selection == PASSKEY && !passkey.empty())
                passkey.pop_back();
            break;
		case KEY_ENTER: // from numpad
        case '\n':
        case '\r':
            if (current_selection == LOGIN && login()){
				app->switchPage("home");
			}
			break;
        default:
            if (ch >= 32 && ch <= 126) { // Printable ASCII
				echo();
                char c = static_cast<char>(ch);
                if (current_selection == USERNAME)
                    username += c;
                else if (current_selection == EMAIL)
                    email += c;
                else if (current_selection == PASSKEY)
                    passkey += c;
				noecho();
            }
            break;
    }
}

bool AppPages::AuthPage::login() {
	// login process
	// AppModels::User user;
    std::string token = getPasskey();


    if ( AppControllers::Auth::login(token)) {
		user.repos = AppControllers::Repo::fetchUserRepos();
		return true;
    }
	return false;

}

void AppPages::AuthPage::clearValues(){
	email = "";
	username = "";
	passkey = "";
	current_selection = 0;
}