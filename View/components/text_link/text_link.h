#ifndef TEXT_LINK_H
#define TEXT_LINK_H

#include <string>

using uint = unsigned int;

namespace AppComponent{
        void textLink(uint id, std::string label, bool isSelected, uint line_height, uint margin);
}

#endif