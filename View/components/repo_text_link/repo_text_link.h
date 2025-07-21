#ifndef REPO_TEXT_LINK_H
#define REPO_TEXT_LINK_H

#include <string>
#include "../base_component/base_component.h"

using uint = unsigned int;

namespace AppComponent{
    class RepoTextLink: public BaseComponent{
        private:
            std::string label;
            std::string description;
            int label_color_scheme;
            int description_color_scheme;
        public:
            RepoTextLink(uint height, uint width, std::string label, std::string description) : BaseComponent(height, width){
                this->label = label;
                this->description = description;
                label_color_scheme = 3;
                description_color_scheme = 7;
            }
            void display(uint line_height, uint margin, bool isSelected, std::string link, bool is_private);
            void changeColorScheme(int color);
            void onClick();
    };
}

#endif