#include <string>
#include <ncurses.h>
#include "text_with_label.h"

using uint = unsigned int;

void AppComponent::stringInputComponent(unsigned int id, std::string label, std::string value, bool isSelected, unsigned int line_height, unsigned int margin) {
        
        attron(A_BOLD | COLOR_PAIR(8));
        mvprintw(line_height, margin+1, label.c_str());
        if (isSelected) {
                attron(A_REVERSE); // Highlight selected field
        }
        mvprintw(line_height + 1, margin, "▶ %s", value.c_str());
        if(isSelected) {
                attroff(A_REVERSE);
        }
        attroff(A_BOLD | COLOR_PAIR(8));
}