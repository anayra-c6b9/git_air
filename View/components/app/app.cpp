#include "app.h"
#include <ncurses.h>
#include "../../globals.h"
#include "../../../all_globals.h"

void AppComponent::App::run() {
    int ch;
    while ((ch = getch())) {
        clear();
        current_page->display();
        if(current_page->hasFooter)
            menu_bar.displayMenuBar();
        if(isEscapeMode()){
            attron(COLOR_RED);
            mvaddstr(0,0, "ESC mode");
            attroff(COLOR_RED);
        }
        refresh();
        current_page->handleInput(ch, this);
    }
}

void AppComponent::App::switchPage(const std::string& pageName) {
    if (pages.find(pageName) != pages.end()) {
        current_page_name = pageName;
        current_page = pages[pageName];
    }
}

void AppComponent::App::toggleMode(){
    is_mod = !is_mod;
}

bool AppComponent::App::isEscapeMode(){
    return is_mod;
}

void AppComponent::App::quit() {
    // End ncurses mode cleanly
    endwin();
    // When this method returns, destructor (~App) will be called
    exit(0); // optional
}

void AppComponent::App::handleModeKey(int ch){
    // if current instance is of loading page return
    if (current_page_name == "loading_screen"){
        return;
    }
    switch(ch){
        case KEY_ESC: AppComponent::App::toggleMode();
            break;
        case 66:
        case 98: 
            if(current_page_name != "auth"){
                switchPage("home");
            }
            // check if the instance is not of auth
            // if not navigate to home
            break;
        case 71:
        case 111:
            // code to clear the user data in model
            // navigate to auth page
            user.clearValues();
            pages["auth"]->clearValues();
            switchPage("auth");
            break;
        case 81:
        case 113:
            // quit safely
            quit();
            break;
        default:
            break;
    }
}
