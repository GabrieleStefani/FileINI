#include <iostream>
#include "INIManager.h"

int main() {
    INIManager im;
    for(auto &section : im.readFile("config.ini"))
    {
        std::cout << "[" << section.first << "]" << std::endl;
        for(auto elem : (**section.second)){
            std::cout << elem.first << "=" << elem.second << std::endl;
        }
    }
    return 0;
}