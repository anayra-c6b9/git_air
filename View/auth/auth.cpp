#include "auth.h"
#include <string>
#include <ncurses.h>
#include "../globals.h"
#include "../components/text_with_label/text_with_label.h"

using uint = unsigned int;

uint AuthNS::AuthWindow::window_number = 0;
uint AuthNS::AuthWindow::window_created = 0;

void AuthNS::AuthWindow::setEmail(std::string email) {
	this->email = email;
}

std::string AuthNS::AuthWindow::getEmail() {
	return email;
}

void AuthNS::AuthWindow::setUsername(std::string username) {
	this->username = username;
}

std::string AuthNS::AuthWindow::getUsername() {
	return username;
}

void AuthNS::AuthWindow::setPasskey(std::string passkey) {
	this->passkey = passkey;
}

std::string AuthNS::AuthWindow::getPasskey() {
	return passkey;
}

void AuthNS::AuthWindow::toggleIsUserSaved() {
	is_user_saved = !is_user_saved;
}

bool AuthNS::AuthWindow::getIsUserSaved() {
	return is_user_saved;
}

bool AuthNS::AuthWindow::login() {
	// login process
	return true;
}

int getExtraSpace(int winSize, int len) {
		int extra_length = winSize - len > 0 ? winSize - len : 0;
		return extra_length;
}

int getLesser(int param1, int param2) {
		return param1 < param2 ? param1 : param2;
}

void AuthNS::AuthWindow::displayAuthPage() {
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
		for(int i = 0; i < (sizeof(auth_data)/sizeof(auth_data[0])); i++){
				AppComponent::stringInputComponent(auth_data[i].id, auth_data[i].label, iter_y + i*3, iter_x);
		}

		// input
		
}

