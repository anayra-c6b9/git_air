#ifndef APP_H
#define APP_H

#include "../page/page.h"
#include "../../Pages/auth/auth.h"
#include "../../Pages/loading_screen/loading_screen.h"
#include <map>
#include <string>

namespace AppComponent {
    class App {
    private:
        AppComponent::Page* currentPage;
        std::map<std::string, AppComponent::Page*> pages;

    public:
        App() {
            // Add pages here
            pages["auth"] = new AppPages::AuthPage();
            pages["loading_screen"] = new AppPages::LoadingScreen();
            currentPage = pages["loading_screen"];
        }

        void run();
        void switchPage(const std::string& pageName);

        ~App(){
            for (auto& pair : pages) delete pair.second;
        }
};

}

#endif