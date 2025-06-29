#include "base_component.h"

using uint = unsigned int;

void AppComponent::BaseComponent::setComponentHeight(uint height){
        component_height = height;
}

void AppComponent::BaseComponent::setComponentWidth(uint width){
        component_width = width;
}

uint AppComponent::BaseComponent::getComponentHeight(){
        return component_height;
}

uint AppComponent::BaseComponent::getComponentWidth(){
        return component_width;
}
