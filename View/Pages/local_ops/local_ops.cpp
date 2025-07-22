#include "local_ops.h"
#include <ncurses.h>
#include <string>
#include "../../components/app/app.h"
#include "../../components/button_with_label/button_with_label.h"
#include "../../globals.h"

#include "../../../Model/user/muser.h"
#include "../../../Model/local_repo/mlocal_repo.h"
#include "../../../Controller/repo/crepo.h"

#include "../../../all_globals.h"

using uint = unsigned int;

static int getExtraSpace(int winSize, int len) {
		int extra_length = winSize - len > 0 ? winSize - len : 0;
		return extra_length;
}

static int getLesser(int param1, int param2) {
		return param1 < param2 ? param1 : param2;
}

void AppPages::LocalOpsPage::display(){
    int lower_limit,
		extraSpace = 0,
		title_length = 12,
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
    mvaddstr(1, lower_limit, "┃ GIT REPO ┃");
    // if(title_length - 3 <= app_win.getAppWinWidth()){
    // }
    mvaddstr(2, lower_limit, "└");
    for(int i = 0; i < title_length-2; i++)
            mvaddstr(2, lower_limit+1+i, "─");
    mvaddstr(2, lower_limit + title_length - 1, "┘");

    local_repo = AppControllers::Repo::getRepoInfo(curr_local_path);

    mvprintw(4, 0, "Repo Name: %s", (local_repo->repo_name).c_str());
    mvprintw(5, 0, "Repo Path: %s", (local_repo->repo_path).c_str());
    mvprintw(6, 0, "Repo default branch: %s", (local_repo->default_branch).c_str());

    attron(COLOR_YELLOW);
    mvhline(7, 1, '-', app_win.getAppWinWidth()-2);
    attroff(COLOR_YELLOW);

    AppComponent::ButtonWithLabel btn(3, 8, "PUSH");
    btn.display(9, 1, current_selection == PUSH);
    if(has_pushed && is_push_touched){
        attron(COLOR_GREEN);
        mvprintw(9, 16, "SUCCESSFULLY PUSHED THE CODE");
        attroff(COLOR_GREEN);
    } else if(is_push_touched) {
        attron(COLOR_GREEN);
        mvprintw(9, 16, "CODE PUSH FAILED. CONFLICT DETECTED");
        attroff(COLOR_GREEN);
    }

    
}

void AppPages::LocalOpsPage::handleInput(int ch, AppComponent::App *app){
    if(app->isEscapeMode()){
		app->handleModeKey(ch);
		return;
	}
	switch (ch) {
        case KEY_ESC:
            app->toggleMode();
            break;
        case KEY_UP:
            if (current_selection > 0){
                current_selection--;
            }
            break;
        case KEY_DOWN:
            if (current_selection < TOTAL_FIELDS - 1){
                current_selection++;
            }
            break;
		case KEY_ENTER: // from numpad
        case '\n':
        case '\r':
            if (current_selection == PUSH){
                is_push_touched = true;
				// wait
                if(pushCode()){
                    has_pushed = true;
                } else {
                    has_pushed = false;
                }
			}
			break;
        default:
            break;
    }
}

void AppPages::LocalOpsPage::clearValues(){}

bool AppPages::LocalOpsPage::pushCode(){
    return local_repo->commitAndPushAll("the new push", the_user_token);
}
