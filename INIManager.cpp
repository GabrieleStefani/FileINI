//
// Created by Lauretta Agliata on 28/08/18.
//

#include "INIManager.h"
#include <fstream>
#include <sstream>
#include <vector>

void INIManager::readFile(std::string fileName) {

    configuration.clear();
    comments.clear();

    std::string currentSection = "";
    std::ifstream infile(fileName);
    std::string line;
    while(std::getline(infile, line)){
        if(line.at(0) == '[' && line.back() == ']' && line.size() > 2){
            line = line.substr(1, line.size() - 2);
            configuration.insert(make_pair(line, std::unique_ptr<std::map<std::string, std::string>>(new std::map<std::string, std::string>())));
            currentSection = line;
        } else if (line.at(0) == ';' || line.at(0) == '#') {
            comments.insert(make_pair(currentSection, line.substr(1, line.size())));
        } else {
            std::stringstream lineStream(line);
            std::string word;
            std::vector<std::string> wordList;
            while (std::getline(lineStream, word, '=')) {
                wordList.push_back(word);
            }
            if (wordList.size() == 2) {
                if (currentSection == "")
                    configuration.insert(make_pair(currentSection, std::unique_ptr<std::map<std::string, std::string>>(new std::map<std::string, std::string>)));
                configuration[currentSection]->insert(make_pair(wordList[0], wordList[1]));
            }else {
                std::cerr << fileName + " doesn't respect the INI format";
                break;
            }
        }
    }
    infile.close();
}

void INIManager::writeFile(std::string fileName) {
    if(fileName.substr(fileName.length() - 4) != ".ini")
        fileName.append(".ini");
    std::ofstream outfile(fileName);
    for(auto &section : configuration)
    {
        if(section.first != "") {
            outfile << "[" << section.first << "]" << std::endl;
            if(comments.find(section.first) != comments.end())
                outfile << ";" + comments[section.first] << std::endl;
        }
        for (auto elem : *section.second) {
            outfile << elem.first << "=" << elem.second << std::endl;
        }
    }
    outfile.close();
}

const std::map<std::string, std::unique_ptr<std::map<std::string, std::string>>> &
INIManager::getConfiguration() const {
    return configuration;
}

const std::map<std::string, std::string> &INIManager::getComments() const {
    return comments;
}

void INIManager::addSection(std::string section) {
    if(configuration.find(section) == configuration.end())
        configuration.insert(make_pair(section, std::unique_ptr<std::map<std::string, std::string>>(new std::map<std::string, std::string>)));
}

void INIManager::removeSection(std::string section) {
    if(configuration.find(section) != configuration.end())
        configuration.erase(section);
}

void INIManager::changeSectionName(std::string oldName, std::string newName) {
    if(configuration.find(oldName) != configuration.end()){
        std::map<std::string, std::string> params;
        params = *configuration[oldName];
        configuration.insert(make_pair(newName, std::unique_ptr<std::map<std::string, std::string>>(&params)));
        configuration.erase(oldName);
    }

}

std::map<std::string, std::string> INIManager::getSection(std::string section) {
    return (*configuration[section]);
}

void INIManager::addParamToSection(std::string key, std::string value, std::string section) {
    if(configuration.find(section) != configuration.end())
        configuration[section]->insert(make_pair(key, value));
}

void INIManager::removeParamFromSection(std::string key, std::string section) {
    if(configuration.find(section) != configuration.end() && configuration[section]->find(key) != configuration[section]->end())
        configuration[section]->erase(key);
}

void INIManager::changeParamInSection(std::string key, std::string newValue, std::string section) {
    if(configuration.find(section) != configuration.end() && configuration[section]->find(key) != configuration[section]->end())
        (*configuration[section])[key] = newValue;
}

std::string INIManager::getParamValueInSection(std::string key, std::string section) {
    if(configuration.find(section) != configuration.end() && configuration[section]->find(key) != configuration[section]->end())
        return (*configuration[section])[key];
    return "Param not found";
}

std::string INIManager::findParamSection(std::string key) {
    for(auto &section : configuration){
        if(section.second->find(key) != section.second->end())
            return section.first;
    }
    return "Param not found";
}

void INIManager::addCommentToSection(std::string comment, std::string section) {
    if(comments.find(section) == comments.end())
        comments.insert(make_pair(section, comment));
}

void INIManager::removeCommentFromSection(std::string section) {
    if(comments.find(section) != comments.end())
        comments.erase(section);
}

void INIManager::changeCommentInSection(std::string newComment, std::string section) {
    if(comments.find(section) != comments.end())
        comments[section] = newComment;
}

std::string INIManager::getCommentFromSection(std::string section) {
    if(comments.find(section) != comments.end())
        return comments[section];
    return "Comment not found";
}

