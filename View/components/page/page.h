#ifndef PAGE_H
#define PAGE_H

// #include "../app/app.h"

namespace AppComponent {
    class App;

    class Page{
        public:
            bool hasFooter;
            virtual void display() = 0;
            virtual  void handleInput(int ch, AppComponent::App *app) = 0;
            virtual ~Page() = default;
    };
}

#endif