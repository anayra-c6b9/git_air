#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <ncurses.h>
#include <stdexcept>
#include "app_window.h"

using uint = unsigned int;

// uint AppComponent::AppWindow::max_win_width = 80;
// uint AppComponent::AppWindow::menu_bar_height = 3;

void AppComponent::AppWindow::setAppWinWidth(int width) {
		max_win_width = (unsigned int)width;
}

void AppComponent::AppWindow::setAppWinHeight(int height) {
		max_win_height = (unsigned int)height;
}

uint AppComponent::AppWindow::getAppWinWidth() {
		return max_win_width;
}

uint AppComponent::AppWindow::getAppWinHeight() {
		return max_win_height;
}

uint AppComponent::AppWindow::getMenuBarHeight() {
		return menu_bar_height;
}

void AppComponent::AppWindow::setWindowSize() {
		winsize win;

		try
		{
			// set terminal size
			if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == 0){
					setAppWinWidth(win.ws_col);
					setAppWinHeight(win.ws_row);
			} else {
					int w, h;
					getmaxyx(stdscr, h, w);
					setAppWinWidth(w);
					setAppWinHeight(h);

					if (w <= 0 || h <= 0) {
							throw std::runtime_error("Terminal Size cannot be determined");
					}
				
			}

			// resize terminal for ncurses
			if(resizeterm(getAppWinHeight(), getAppWinWidth()) == ERR){
					throw std::runtime_error("Failed to resize Terminal");
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			
		}
	
}



