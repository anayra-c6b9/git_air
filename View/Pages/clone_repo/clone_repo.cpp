#include "clone_repo.h"
#include <string>
#include <ncurses.h>
#include "../../globals.h"
#include "../../components/text_with_label/text_with_label.h"
#include "../../components/app/app.h"
#include "../../components/button_with_label/button_with_label.h"

using uint = unsigned int;

static int getExtraSpace(int winSize, int len) {
		int extra_length = winSize - len > 0 ? winSize - len : 0;
		return extra_length;
}

static int getLesser(int param1, int param2) {
		return param1 < param2 ? param1 : param2;
}

void AppPages::CloneRepoPage::display(){
    int lower_limit,
		extraSpace = 0,
		title_length = 14,
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
		mvaddstr(1, lower_limit, "┃ CLONE REPO ┃");
		// if(title_length - 3 <= app_win.getAppWinWidth()){
		// }
		mvaddstr(2, lower_limit, "└");
		for(int i = 0; i < title_length-2; i++)
				mvaddstr(2, lower_limit+1+i, "─");
		mvaddstr(2, lower_limit + title_length - 1, "┘");

		// UI

		// creating a button object
		std::string button_label_name = "Clone";
		AppComponent::ButtonWithLabel button(3 /*height*/, button_label_name.length() + 4, button_label_name);

		AppComponent::stringInputComponent(page_data[0].id, page_data[0].label, link, current_selection == LINK, iter_y + 0*3, iter_x);
		AppComponent::stringInputComponent(page_data[1].id, page_data[1].label, path, current_selection == PATH, iter_y + 1*3, iter_x);
		
		extraSpace = getExtraSpace(app_win.getAppWinWidth(), button_label_name.length());
		lower_limit = extraSpace/2;
		button.display(iter_y + 2*3, lower_limit, current_selection == CLONE);

}

void AppPages::CloneRepoPage::handleInput(int ch, AppComponent::App *app) {
	
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
            if (current_selection == LINK && !link.empty())
                link.pop_back();
            else if (current_selection == PATH && !path.empty())
                path.pop_back();
            break;
		case KEY_ENTER: // from numpad
        case '\n':
        case '\r':
            if (current_selection == CLONE && clone()){
				// wait
			}
			break;
        default:
            if (ch >= 32 && ch <= 126) { // Printable ASCII
				echo();
                char c = static_cast<char>(ch);
                if (current_selection == LINK)
                    link += c;
                else if (current_selection == PATH)
                    path += c;
				noecho();
            }
            break;
    }
}

bool AppPages::CloneRepoPage::clone() {
	// login process
	// AppModels::User user;
    

}