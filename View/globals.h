#ifndef GLOBALS_H
#define GLOBALS_H

#include "components/app_window/app_window.h"
#include "components/menu_bar/menu_bar.h"
#include "components/app/app.h"
#include <string>

// window size
extern AppComponent::AppWindow app_win;
extern AppComponent::MenuBar menu_bar;
extern AppComponent::App app;
extern std::string curr_local_path;
extern std::string the_user_token;

#endif
