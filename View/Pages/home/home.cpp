#include "home.h"
#include <ncurses.h>
#include <string>
#include "../../globals.h"

#include "../../components/text_link/text_link.h"
#include "../../components/app/app.h"

#include "../../../all_globals.h"

static int getExtraSpace(int winSize, int len) {
		int extra_length = winSize - len > 0 ? winSize - len : 0;
		return extra_length;
}

static int getLesser(int param1, int param2) {
		return param1 < param2 ? param1 : param2;
}

void AppPages::HomePage::display(){
    int lower_limit,
		extraSpace = 0,
		title_length = 8,
		margin = 0,
		iter_y = 6,
		iter_x = 1;

    extraSpace = getExtraSpace(app_win.getAppWinWidth(), title_length);
    lower_limit = extraSpace/2;

    mvaddstr(0, lower_limit, "┌");
    for(int i = 0; i < title_length - 2; i++)
            mvaddstr(0, lower_limit+1+i, "─");
    mvaddstr(0, lower_limit + title_length - 1, "┐");
    // mvaddwstr(2, lower_limit, L"\u2503 ADD GITHUB CREDENTIALS \u2503");
    mvaddstr(1, lower_limit, "┃ HOME ┃");
    // if(title_length - 3 <= app_win.getAppWinWidth()){
    // }
    mvaddstr(2, lower_limit, "└");
    for(int i = 0; i < title_length-2; i++)
            mvaddstr(2, lower_limit+1+i, "─");
    mvaddstr(2, lower_limit + title_length - 1, "┘");

    attron(COLOR_PAIR(2));
    mvprintw(4, 2, "welcome %s", user.getUsername().c_str());
    attroff(COLOR_PAIR(2));
    // UI

    AppComponent::textLink(page_element[0].id, page_element[0].label, current_selection == field1, iter_y + 0*3, iter_x);
    AppComponent::textLink(page_element[1].id, page_element[1].label, current_selection == field2, iter_y + 1*3, iter_x);
    AppComponent::textLink(page_element[2].id, page_element[2].label, current_selection == field3, iter_y + 2*3, iter_x);

}

void AppPages::HomePage::handleInput(int ch, AppComponent::App *app){
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
        case KEY_ENTER: // from numpad
        case '\n':
        case '\r':
            app->switchPage(page_element[current_selection].navigate_to);
            break;
        default:
            
            break;
    }
}

void AppPages::HomePage::clearValues(){}