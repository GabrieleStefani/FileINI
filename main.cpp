#include <iostream>
#include "INIManager.h"

int main() {
    INIManager im;
    im.readFile("config.ini");
    for(auto &section : im.getConfiguration())
    {
        if(section.first != "") {
            std::cout << "[" << section.first << "]" << std::endl;
            if(im.getComments().find(section.first) != im.getComments().end())
                std::cout << ";" + im.getComments().at(section.first) << std::endl;
        }
        for (auto elem : *section.second) {
            std::cout << elem.first << "=" << elem.second << std::endl;
        }
    }
    //im.writeFile( "config2");
    return 0;
}