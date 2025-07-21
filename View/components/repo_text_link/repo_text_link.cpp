#include "./repo_text_link.h"

#include <ncurses.h>
#include <string>
#include "../../globals.h"

void AppComponent::RepoTextLink::display(uint line_height, uint margin, bool isSelected, std::string link, bool is_private){     
        
    if (isSelected) {
            attron(A_REVERSE); // Highlight selected field
    }
    mvaddstr(line_height, margin, "Repository Name: ");
    attron(A_BOLD | COLOR_PAIR(label_color_scheme));
    mvprintw(line_height, margin + 17, "%s", label.c_str());
    attroff(A_BOLD | COLOR_PAIR(label_color_scheme));
    if(isSelected) {
            attroff(A_REVERSE);
    }

    if(is_private){
        attron(COLOR_GREEN);
        mvaddstr(line_height + 1, margin, "Private Repo");
        attroff(COLOR_GREEN);
    } else {
        attron(COLOR_RED);
        mvaddstr(line_height+1, margin, "Public Repo");
        attroff(COLOR_RED);
    }

    std::string desc = description.substr(0, (app_win.getAppWinWidth() - 6) < description.size() ? app_win.getAppWinWidth() - 6 : description.size());
    mvprintw(line_height + 2, margin, "Description: %s...", desc.c_str());
    
    
}

void AppComponent::RepoTextLink::changeColorScheme(int color){}

void AppComponent::RepoTextLink::onClick(){}