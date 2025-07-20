#include "browse.h"
#include "../../globals.h"
#include "../../components/text_with_label/text_with_label.h"
#include "../../components/button_with_label/button_with_label.h"
#include "../../components/app/app.h"
#include "../../globals.h"

#include <ncurses.h>

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
    
}

void AppPages::BrowsePage::handleInput(int ch, AppComponent::App *app){
    switch (ch) {
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
            if (current_selection == BROWSE && browse()){
				app->switchPage("home");
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