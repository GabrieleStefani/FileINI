//
// Created by Lauretta Agliata on 28/08/18.
//

#ifndef FILEINI_INIPARSER_H
#define FILEINI_INIPARSER_H

#include <iostream>
#include <map>
#include <list>
#include "NotFoundException.h"

class INIManager {
public:

    void readFile(std::string fileName);
    void writeFile(std::string fileName);

    void addCommentToSection(std::string comment, std::string section);
    void removeCommentFromSection(std::string section);
    void changeCommentInSection(std::string newComment, std::string section);
    std::string getCommentFromSection(std::string section);

    void addSection(std::string section);
    void removeSection(std::string section);
    void changeSectionName(std::string oldName, std::string newName);
    std::map<std::string, std::string> getSection(std::string section);

    void addParamToSection(std::string key, std::string value, std::string section);
    void removeParamFromSection(std::string key, std::string section);
    void changeParamInSection(std::string key, std::string newValue, std::string section);
    std::string getParamValueInSection(std::string key, std::string section);

    std::list<std::string> findParamSection(std::string key);

    const std::map<std::string, std::unique_ptr<std::map<std::string, std::string> >> &getConfiguration() const;
    const std::map<std::string, std::string> &getComments() const;

private:
    std::map<std::string, std::unique_ptr<std::map<std::string, std::string>>> configuration;
    std::map<std::string, std::string> comments;
};


#endif //FILEINI_INIPARSER_H
