#ifndef BUTTON_WITH_LABEL_H
#define BUTTON_WITH_LABEL_H

#include <string>
#include "../base_component/base_component.h"

using uint = unsigned int;
namespace AppComponent {
    class ButtonWithLabel: public BaseComponent{
        private:
            std::string label;
            int color_scheme;
        public:
            ButtonWithLabel(uint height, uint width, std::string label) : BaseComponent(height, width){
                this->label = label;
                color_scheme = 4; // default color scheme
            }
            void display(uint line_height, uint margin, bool isSelected);
            void changeColorScheme(int color);
            void onClick();
    };
}

#endif