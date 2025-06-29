#include <string>
#include <ncurses.h>
#include "text_with_label.h"

using uint = unsigned int;

void AppComponent::stringInputComponent(uint id, std::string label, uint line_height, uint margin) {

        attron(A_BOLD | COLOR_PAIR(8));
        mvprintw(line_height, margin+1, label.c_str());
        attroff(A_BOLD | COLOR_PAIR(8));
        mvprintw(line_height + 1, margin, "▶");
}