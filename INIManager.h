//
// Created by Lauretta Agliata on 28/08/18.
//

#ifndef FILEINI_INIPARSER_H
#define FILEINI_INIPARSER_H

#include <iostream>
#include <map>

class INIManager {
public:

    std::map<std::string, std::unique_ptr<std::map<std::string, std::string>*>> readFile(std::string fileName);
private:
    std::string fileName;
};


#endif //FILEINI_INIPARSER_H
