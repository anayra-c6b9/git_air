#include <sys/ioctl.h>
#include <unistd.h>
#include "app_window.h"

using uint = unsigned int;

// uint AppComponent::AppWindow::max_win_width = 80;
// uint AppComponent::AppWindow::menu_bar_height = 3;

void AppComponent::AppWindow::setAppWinWidth(int width) {
	max_win_widht = (unsigned int)width;
}

void AppComponent::AppWindow::setAppWinHeight(int height) {
	max_win_height = (unsigned int)height;
}

uint AppComponent::AppWindow::getAppWinWidth() {
	return max_win_widht;
}

uint AppComponent::AppWindow::getAppWinHeight() {
	return max_win_height;
}

uint AppComponent::AppWindow::getMenuBarHeight() {
	return menu_bar_height;
}

void AppComponent::AppWindow::setWindowSize() {
	winsize win;
	
	// get terminal window size
	if(ioctl(STDOUT_FILENO, TIOCSWINSZ, &win) == 0){
		AppComponent::AppWindow::setAppWinWidth(win.ws_col);
		AppComponent::AppWindow::setAppWinHeight(win.ws_row);
	} else {
		// throw error
	}
}

