#include "loading_screen.h"
#include "../../globals.h"
#include "../../components/app/app.h"

#include <thread> // pause
#include <chrono> // time in ms

using uint = unsigned int;

static int getExtraSpace(int winSize, int len) {
		int extra_length = winSize - len > 0 ? winSize - len : 0;
		return extra_length;
}

static int getLesser(int param1, int param2) {
		return param1 < param2 ? param1 : param2;
}

// pause time utility
void AppPages::LoadingScreen::pauseTime() {
    if(loaded.load() >= 100) return;
    try{
        for(int i = 0; i < 100; i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(pause_time[i]));
            loaded++;
        }
    } catch (const std::exception& ex){
        // handle error here
        // std::cerr << "[Thread Error]"<<ex.what() <<std::endl;
    } catch (...) {
        // cathc all unexpected errors
        // std::cerr << "[Thread Error] Unknown exception occured" <<std::endl;
    }
    
}

void AppPages::LoadingScreen::display() {
    int lower_limit,
		extraSpace = 0,
		title_length = 54,
        loading_bar_length = 52,
        enter_string = 17;

	extraSpace = getExtraSpace(app_win.getAppWinWidth(), title_length);
	lower_limit = extraSpace/2;

    mvaddstr(0, lower_limit, "  /$$$$$$  /$$   /$$            /$$$$$$  /$$");
    mvaddstr(1, lower_limit, " /$$__  $$|__/  | $$           /$$__  $$|__/");       
    mvaddstr(2, lower_limit, "| $$  \\__/ /$$ /$$$$$$$       | $$  \\ $$ /$$ /$$$$$$");
    mvaddstr(3, lower_limit, "| $$  \\ $$| $$/ | $$  /       | $$  | $$| $$| $$   $$");
    mvaddstr(4, lower_limit, "| $$ /$$$$| $$|_  $$_/        | $$$$$$$$| $$| $$  \\__/");
    mvaddstr(5, lower_limit, "| $$|_  $$| $$  | $$          | $$__  $$| $$| $$");
    mvaddstr(6, lower_limit, "|  $$$$$$/| $$  |  $$$$/      | $$  | $$| $$| $$");   
    mvaddstr(7, lower_limit, "\\______/  |__/   \\____/       |__/  |__/|__/|__/");  

    extraSpace = getExtraSpace(app_win.getAppWinWidth(), loading_bar_length);
    lower_limit = extraSpace/2;

    mvprintw(app_win.getAppWinHeight() - 4, lower_limit + loading_bar_length - 5, "[%d]", loaded.load());
    mvaddch(app_win.getAppWinHeight() - 3, lower_limit, '[');
    mvhline(app_win.getAppWinHeight() - 3, lower_limit + 1, '#', loaded.load()/2);
    mvaddch(app_win.getAppWinHeight() - 3, lower_limit + loading_bar_length - 1, ']');

    if(loaded.load() >= 100){
        extraSpace = getExtraSpace(app_win.getAppWinWidth(), enter_string);
        lower_limit = extraSpace/2;

        mvaddstr(app_win.getAppWinHeight() - 5, lower_limit, ">> PRESS ENTER <<");
    }

}
void AppPages::LoadingScreen::handleInput(int ch, AppComponent::App *app) {
    if(loaded.load() < 100) return;
    switch(ch){
        case KEY_ENTER: // from numpad
        case '\n':
        case '\r':
            app->switchPage("auth");
            break;
        default: break;
    }
}
void AppPages::LoadingScreen::navigateToNext() {}