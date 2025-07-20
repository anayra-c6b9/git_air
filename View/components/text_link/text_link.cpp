#include <string>
#include <ncurses.h>
#include "text_link.h"

using uint = unsigned int;

void AppComponent::textLink(unsigned int id, std::string label, bool isSelected, unsigned int line_height, unsigned int margin) {
        
        attron(A_BOLD | COLOR_PAIR(8));
        if (isSelected) {
                attron(A_REVERSE); // Highlight selected field
        }
        mvprintw(line_height, margin+1, label.c_str());
        if(isSelected) {
                attroff(A_REVERSE);
        }
        attroff(A_BOLD | COLOR_PAIR(8));
}