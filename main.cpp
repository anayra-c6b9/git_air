#include "all_globals.h"
#include "View/index.h"


AppModels::User user;

int main() {
    AppView::runUI();

    return 0;
}

// int main() {
//     AppModels::User user;
//     std::string token;

//     std::cout << "Enter your GitHub Personal Access Token: ";
//     std::cin >> token;

//     if (AppControllers::Auth::login(user, token)) {
//         std::cout << "\n✅ Login Successful!\n";
//         std::cout << "Name: " << user.getName() << "\n";
//         std::cout << "Username: " << user.getUsername() << "\n";
//         std::cout << "Email: " << user.getEmail() << "\n";

//         // Optionally store token for later
//         // std::ofstream outfile("token.txt");
//         // outfile << token;
//         // outfile.close();
//     } else {
//         std::cerr << "\n❌ Login Failed. Check your token.\n";
//     }

//     return 0;
// }
