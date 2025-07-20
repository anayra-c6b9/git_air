#include "button_with_label.h"
#include <ncurses.h>

using uint = unsigned int;

void AppComponent::ButtonWithLabel::display(uint line_height, uint margin, bool isSelected) {
    
    attron(A_BOLD | COLOR_PAIR(color_scheme));
    
    
    if (isSelected) {
            attron(A_REVERSE); // Highlight selected field
    }
    // line 1
    mvaddstr(line_height, margin, "┌");
    for(int i = 0; i < label.length() + 2; i++)
				mvaddstr(line_height, margin+1+i, "─");
    mvaddstr(line_height, margin+label.length()+3, "┐");

    // line 2
    mvprintw(line_height + 1, margin, "┃ %s ┃", label.c_str());

    // line 3
    mvaddstr(line_height + 2, margin, "└");
    for(int i = 0; i < label.length() + 2; i++)
				mvaddstr(line_height + 2, margin+1+i, "─");
    mvaddstr(line_height + 2, margin+label.length()+3, "┘");

    if(isSelected) {
            attroff(A_REVERSE);
    }
    attroff(A_BOLD | COLOR_PAIR(color_scheme));
}

void AppComponent::ButtonWithLabel::changeColorScheme(int color){
    color_scheme = color;
}


