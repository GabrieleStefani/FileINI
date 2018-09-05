#include <iostream>
#include "INIManager.h"

int main() {
    INIManager im;
    for(auto elem : im.readFile("config.ini"))
    {
        std::cout << elem.first << " " << elem.second << std::endl;
    }
    return 0;
}