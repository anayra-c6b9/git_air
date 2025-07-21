#include "user_repos.h"
#include <ncurses.h>
#include <string>
#include "../../components/app/app.h"
#include "../../components/repo_text_link/repo_text_link.h"
#include "../../globals.h"
#include "../../../Model/user/muser.h"
#include "../../../all_globals.h"

using uint = unsigned int;

static int getExtraSpace(int winSize, int len) {
		int extra_length = winSize - len > 0 ? winSize - len : 0;
		return extra_length;
}

static int getLesser(int param1, int param2) {
		return param1 < param2 ? param1 : param2;
}

void AppPages::UserReposPage::display(){
    int lower_limit,
		extraSpace = 0,
		title_length = 21,
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
    mvaddstr(1, lower_limit, "┃ USER REPOSITORIES ┃");
    // if(title_length - 3 <= app_win.getAppWinWidth()){
    // }
    mvaddstr(2, lower_limit, "└");
    for(int i = 0; i < title_length-2; i++)
            mvaddstr(2, lower_limit+1+i, "─");
    mvaddstr(2, lower_limit + title_length - 1, "┘");

    user_repos = user.repos;
    // get the repo data from repo model

    // if(!hasRepos){
    //     attron(COLOR_RED);
    //     mvprintw(5, 2, "Cannot fetch user repos. Login again");
    //     attroff(COLOR_RED);
    //     return;
    // }

    if(user_repos.empty()){
        attron(COLOR_RED);
        mvprintw(5,2, "<< No repositories created >>");
        attroff(COLOR_RED);
        return;
    }

	// UI
    setViewItemFrequency(3, app_win.getAppWinHeight() - 4);
    if(current_selection >= last_selection){
        if(current_selection < view_item_freq){
            starting_point = 0;
            ending_point = starting_point + view_item_freq - 1;
        } else {
            starting_point = current_selection - view_item_freq + 1;
            ending_point = current_selection;
        }
    } else {
        if(current_selection < view_item_freq){
            starting_point = 0;
            ending_point = starting_point + view_item_freq - 1;
        } else {
            starting_point = current_selection - view_item_freq + 1;
            ending_point = current_selection;
        }
    }

    if (ending_point >= user_repos.size()) {
        ending_point = user_repos.size() - 1;
    }

    for(int i = starting_point, j = 0; i <= ending_point && j < view_item_freq; i++, j++){
        AppComponent::RepoTextLink repo(4, user_repos.at(i).name.size(), user_repos.at(i).name, user_repos.at(i).description);
        repo.display(3 + j*4, 1, current_selection == i, user_repos.at(i).html_url, user_repos.at(i).privateRepo);
    }
}

void AppPages::UserReposPage::handleInput(int ch, AppComponent::App *app){
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
                last_selection = current_selection;
                current_selection--;
            }
            break;
        case KEY_DOWN:
            if (current_selection < user_repos.size() - 1){
                last_selection = current_selection;
                current_selection++;
            }
            break;
		case KEY_ENTER: // from numpad
        case '\n':
        case '\r':
            if (current_selection){
				// wait
			}
			break;
        default:
            break;
    }
}

void AppPages::UserReposPage::clearValues(){

}

void AppPages::UserReposPage::setViewItemFrequency(uint upper_limit, uint lower_limit){
    uint diff = lower_limit - upper_limit - 1;
    view_item_freq = diff / 4;
    if(view_item_freq == 0){
        view_item_freq = 1;
    }
}
