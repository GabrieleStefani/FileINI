#include <iostream>
#include "INIManager.h"

int main() {
    INIManager im;
    im.readFile("config.ini");
    for(auto it = im.getConfiguration().begin(); it != im.getConfiguration().end(); it++)
    {
        std::cout << "[" << it->first << "]" << std::endl;
        for(auto elem : (**(it->second))){
            std::cout << elem.first << "=" << elem.second << std::endl;
        }
    }
    im.writeFile("config2");
    return 0;
}