#ifndef MREPO_H
#define MREPO_H

#include <string>

namespace AppModels {
    class Repo {
    public:
        std::string name;
        std::string full_name;
        std::string description;
        bool privateRepo;
        std::string html_url;
    };
}

#endif
