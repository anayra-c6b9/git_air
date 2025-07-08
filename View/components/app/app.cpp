#include "app.h"
#include <ncurses.h>
#include "../../globals.h"

void AppComponent::App::run() {
    int ch;
    while ((ch = getch()) != 'q') {
        clear();
        currentPage->display();
        if(currentPage->hasFooter)
            menu_bar.displayMenuBar();
        refresh();
        currentPage->handleInput(ch, this);
    }
}

void AppComponent::App::switchPage(const std::string& pageName) {
    if (pages.find(pageName) != pages.end()) {
        currentPage = pages[pageName];
    }
}

