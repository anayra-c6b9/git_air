#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <ncurses.h>
#include <bitset>
#include <string>
#include "../base_component/base_component.h"

#define KEY_ESC 27

namespace AppComponent{
        class MenuBar: BaseComponent{
                public:
                        const std::string mb_ESC = "ESC - to enter normal mode";
                        const std::string mb_ENTER = "ENTER - to select option/enter write mode";
                        const std::string mb_B = "B - back";
                        const std::string mb_O = "O - to logout";
                        const std::string mb_Q = "Q - quit";

                        MenuBar(){
                                setComponentHeight(3);
                        }
                        void displayMenuBar();
        };

        class MenuBarControls{
                // hard coding the menubar options
                /*
                ESC - to enter normal mode
                Enter - to select option/enter write mode
                B - back
                Q - quit
                O - to logout
                V - to paste from current keypad
                */
                private:
                        // const std::string mb_ESC = "ESC - to enter normal mode";
                        // const std::string mb_ENTER = "ENTER - to select option/enter write mode";
                        // const std::string mb_B = "B - back";
                        // const std::string mb_O = "O - to logout";
                        // const std::string mb_Q = "Q - quit";
                        static const int mk_ESC = KEY_ESC;
                        static const int mk_ENTER = KEY_ENTER;
                        static const int mk_B = 66;
                        static const int mk_Q = 81;
                        static const int mk_O = 79;
                        static const int mk_b = 98;
                        static const int mk_q = 113;
                        static const int mk_o = 111;
                        static std::bitset<1000> mk_flags;
                public:
                        MenuBarControls(){
                                // hardcoded key values
                                mk_flags[mk_ESC] = true;
                                mk_flags[mk_ENTER] = true;
                                mk_flags[mk_b] = true;
                                mk_flags[mk_Q] = true;
                                mk_flags[mk_O] = true;
                                mk_flags[mk_b] = true;
                                mk_flags[mk_q] = true;
                                mk_flags[mk_o] = true;
                        }
                        
                        bool checkKeyPress(int ch);
                        void executeKeyProgram(int ch);
                        bool initiateKeyPress(int ch);
        };
}

#endif