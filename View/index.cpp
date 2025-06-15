#include <ncurses.h>
#include "auth/index.h"

int main() {
	
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	
	while(1){
		clear();
		Auth::display_auth_page();
		int ch = getch();

		if(ch == KEY_UP) break;
	}

	endwin();

	return 0;
}
