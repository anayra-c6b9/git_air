#include "browse.h"
#include "../../globals.h"
#include "../../components/text_with_label/text_with_label.h"
#include "../../components/button_with_label/button_with_label.h"
#include "../../components/app/app.h"
#include "../../globals.h"
#include "../../colors/color_pair.h"

#include "../../../Controller/repo/crepo.h"

#include <ncurses.h>
#include <string>

static int getExtraSpace(int winSize, int len) {
		int extra_length = winSize - len > 0 ? winSize - len : 0;
		return extra_length;
}

static int getLesser(int param1, int param2) {
		return param1 < param2 ? param1 : param2;
}

void AppPages::BrowsePage::display() {

    int lower_limit,
		extraSpace = 0,
		title_length = 10,
		margin = 0,
		iter_y = 6,
		iter_x = 1;

    extraSpace = getExtraSpace(app_win.getAppWinWidth(), title_length);
    lower_limit = extraSpace/2;
    // simple UI
    AppComponent::stringInputComponent(0, "Enter the Path/Link to the repo", path, PATH == current_selection, 1, 2);
    AppComponent::ButtonWithLabel browse_btn(3, 10, "Browse");
    browse_btn.display(4, lower_limit, BROWSE == current_selection);

    if(is_checked) {
        if(is_valid_repo){
            attron(COLOR_PAIR(2));
            mvaddstr(9, lower_limit, "Valid Repo");

            attroff(COLOR_PAIR(2));
        } else {
            attron(COLOR_PAIR(1));
            mvaddstr(9, lower_limit, "Invalid Repo");
            attroff(COLOR_PAIR(1));
        }
    }
    
}

void AppPages::BrowsePage::handleInput(int ch, AppComponent::App *app){
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
            if (current_selection == PATH && !path.empty())
                path.pop_back();
            break;
		case KEY_ENTER: // from numpad
        case '\n':
        case '\r':
            if (current_selection == BROWSE && checkGitRepository()){
                is_checked = true;
                is_valid_repo = true;
                curr_local_path = path;
                app->switchPage("local_ops");
			} else {
                is_checked = true;
                is_valid_repo = false;
            }
			break;
        default:
            if (ch >= 32 && ch <= 126) { // Printable ASCII
				echo();
                char c = static_cast<char>(ch);
                if (current_selection == PATH)
                    path += c;
				noecho();
            }
            break;
    }
}

bool AppPages::BrowsePage::browse() {

}

void AppPages::BrowsePage::clearValues(){}

bool AppPages::BrowsePage::checkGitRepository(){
    return AppControllers::Repo::isGitRepo(path) ;
}