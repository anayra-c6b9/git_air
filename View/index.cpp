#include <locale.h>
#include <ncurses.h>
#include <csignal>
#include "globals.h"
#include "auth/index.h"
#include "components/app_window/app_window.h"
#include "colors/color_pair.h"

// application window global variable
AppComponent::AppWindow app_win;

void handleSignals(int sig) {
		switch(sig) {
				case SIGWINCH:
						app_win.setWindowSize();
						break;
				default:
						break;
		}

}

int main() {
	
		setlocale(LC_ALL, "");
		initscr();
		noecho();
		cbreak();
		keypad(stdscr, TRUE);
		CustomUtils::init_custom_colors();
		timeout(50);
		
		// get window size
		app_win.setWindowSize();		
		// set signal for window size change
		std::signal(SIGWINCH, handleSignals);

		while(1){
				clear();
				Auth::display_auth_page();
				int ch = getch();
				if(ch == KEY_UP) break;
		}

		endwin();

		return 0;
}
