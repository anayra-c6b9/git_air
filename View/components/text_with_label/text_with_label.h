#ifndef TEXT_WITH_LABEL_H
#define TEXT_WITH_LABEL_H

#include <string>

using uint = unsigned int;

namespace AppComponent{
        void stringInputComponent(uint id, std::string label, std::string value, bool isSelected, uint line_height, uint margin);
}

#endif