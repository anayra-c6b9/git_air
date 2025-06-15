#include "auth.h"
#include <string>

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

