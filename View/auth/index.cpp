#include <ncurses.h>
#include "auth.h"
#include "index.h"
#include "../globals.h"

// lower limit w - 20
// lower limit h - 5

int getExtraSpace(int winSize, int len) {
		int extra_length = winSize - len > 0 ? winSize - len : 0;
		return extra_length;
}

int getLesser(int param1, int param2) {
		return param1 < param2 ? param1 : param2;
}

void Auth::display_auth_page(){
		
		// creating auth window
		AuthNS::AuthWindow auth_win;

		// UI
		// centering the title <<LOGIN TO GITHUB>>
		int lower_limit,
		extraSpace = 0,
		title_length = 26,
		margin = 0;

		extraSpace = getExtraSpace(app_win.getAppWinWidth(), title_length);
		lower_limit = extraSpace/2;

		mvaddstr(0, lower_limit, "┌");
		for(int i = 0; i < title_length - 2; i++)
				mvaddstr(0, lower_limit+1+i, "─");
		mvaddstr(0, lower_limit + title_length - 1, "┐");
		mvaddstr(1, lower_limit, "┃");
		mvaddstr(1, getLesser(lower_limit + title_length - 1, app_win.getAppWinWidth()), "┃");
		// mvaddwstr(2, lower_limit, L"\u2503 ADD GITHUB CREDENTIALS \u2503");
		mvaddstr(2, lower_limit, "┃ ADD GITHUB CREDENTIALS ┃");
		if(title_length - 3 <= app_win.getAppWinWidth()){
				mvaddstr(3, lower_limit, "┃");
				mvaddstr(3, lower_limit + title_length - 1, "┃");
		}
		mvaddstr(4, lower_limit, "└");
		for(int i = 0; i < title_length-2; i++)
				mvaddstr(4, lower_limit+1+i, "─");
		mvaddstr(4, lower_limit + title_length - 1, "┘");

		margin = lower_limit % 4;
		// user email
		attron(A_BOLD | COLOR_PAIR(8));
		mvprintw(6, margin, " Username ");
		attroff(A_BOLD | COLOR_PAIR(8));
		mvprintw(7, margin, ">");
		// user username
		attron(A_BOLD | COLOR_PAIR(8));
		mvprintw(9, margin, " Email ");
		attroff(A_BOLD | COLOR_PAIR(8));
		mvprintw(10, margin, ">");
		// user passkey
		attron(A_BOLD | COLOR_PAIR(8));
		mvprintw(12, margin, " Github Token ");
		attroff(A_BOLD | COLOR_PAIR(8));
		mvprintw(13, margin, ">");
}


