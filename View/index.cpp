#include <locale.h>
#include <ncurses.h>
#include <csignal>
#include "globals.h"
#include "colors/color_pair.h"
#include "index.h"

// application window global variable
AppComponent::AppWindow app_win;
AppComponent::MenuBar menu_bar;
AppComponent::App app;

void handleSignals(int sig) {
		switch(sig) {
				case SIGWINCH:
						app_win.setWindowSize();
						break;
				default:
						break;
		}

}


int AppView::runUI() {
	
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
				// main display section
				app.run();
		}

		endwin();

		return 0;
}
