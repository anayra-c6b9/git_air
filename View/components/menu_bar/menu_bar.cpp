#include <ncurses.h>
#include <string>
#include "menu_bar.h"
#include "../../globals.h"

std::bitset<1000> AppComponent::MenuBarControls::mk_flags;

bool AppComponent::MenuBarControls::checkKeyPress(int ch){
        if(mk_flags[ch]) return true;
        return false;
}

void AppComponent::MenuBarControls::executeKeyProgram(int ch){
        switch(ch){
                case mk_ESC:
                        // escape method
                        return ;
                case mk_ENTER:
                        // enter method
                        return ;
                case mk_B:
                case mk_b:
                        // back method
                        return ;
                case mk_Q:
                case mk_q:
                        // quit method
                        return ;
                case mk_O:
                case mk_o:
                        // logout method
                        return;
                default :
                        // throw some exception
                        return;
        }
}

bool AppComponent::MenuBarControls::initiateKeyPress(int ch){
        if(checkKeyPress(ch)){
                executeKeyProgram(ch);
                return true;
        }

        return false;
}

void AppComponent::MenuBar::displayMenuBar(){
        
        int height = app_win.getAppWinHeight() - 3;
        for(int i = 0; i < app_win.getAppWinWidth(); i++)
            mvaddstr(height,0+i, "▀");
        mvprintw(height + 1, 1, "%s,  %s", mb_ESC.c_str(), mb_ENTER.c_str());
        mvprintw(height + 2, 1, "%s,  %s,  %s", mb_B.c_str(), mb_O.c_str(), mb_Q.c_str());
}

