//
// Created by Lauretta Agliata on 28/08/18.
//

#ifndef FILEINI_INIPARSER_H
#define FILEINI_INIPARSER_H

#include <iostream>
#include <map>

class INIManager {
public:
    void readFile(std::string fileName);
    void writeFile(std::string fileName);

    const std::map<std::string, std::unique_ptr<std::map<std::string, std::string> *>> &getConfiguration() const;

private:
    std::map<std::string, std::unique_ptr<std::map<std::string, std::string>*>> configuration;
    std::map<int, std::string> comments;
};


#endif //FILEINI_INIPARSER_H
