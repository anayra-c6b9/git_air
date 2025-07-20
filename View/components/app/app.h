#ifndef APP_H
#define APP_H

#include "../page/page.h"
#include "../../Pages/auth/auth.h"
#include "../../Pages/loading_screen/loading_screen.h"
#include "../../Pages/home/home.h"
#include "../../Pages/browse/browse.h"
#include "../../Pages/clone_repo/clone_repo.h"
#include <map>
#include <string>

namespace AppComponent {
    class App {
    private:
        AppComponent::Page* current_page;
        std::string current_page_name;
        std::map<std::string, AppComponent::Page*> pages;
        bool is_mod;

    public:
        App() {
            // Add pages here
            pages["auth"] = new AppPages::AuthPage();
            pages["loading_screen"] = new AppPages::LoadingScreen();
            pages["home"] = new AppPages::HomePage();
            pages["browse"] = new AppPages::BrowsePage();
            pages["clone_repo"] = new AppPages::CloneRepoPage();

            current_page = pages["loading_screen"];
            current_page_name = "loading_screen";

            is_mod = false;
        }

        void run();
        void switchPage(const std::string& pageName);
        void toggleMode();
        bool isEscapeMode();
        void quit();
        void handleModeKey(int ch);

        ~App(){
            for (auto& pair : pages) delete pair.second;
        }
};

}

#endif