#include <locale.h>
#include <ncurses.h>
#include <csignal>
#include "globals.h"
#include "colors/color_pair.h"

// application window global variable
AppComponent::AppWindow app_win;
AppComponent::MenuBar menu_bar;

void handleSignals(int sig) {
		switch(sig) {
				case SIGWINCH:
						app_win.setWindowSize();
						break;
				default:
						break;
		}

}

void loadWindow() {

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

		void *loadedWindow = ;

		while(1){
				clear();
				// main display section
				auth_win.displayAuthPage();
				// menu bar
				menu_bar.displayMenuBar();
				int ch = getch();
				if(ch == KEY_UP) break;
		}

		endwin();

		return 0;
}
