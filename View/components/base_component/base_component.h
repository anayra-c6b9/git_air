#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

using uint = unsigned int;

namespace AppComponent{
        class BaseComponent{
                private:
                        uint component_height;
                        uint component_width;

                public:
                        BaseComponent(): component_height(0), component_width(0){}
                        
                        void setComponentHeight(uint height);
                        void setComponentWidth(uint width);
                        uint getComponentHeight();
                        uint getComponentWidth();
        };
}

#endif