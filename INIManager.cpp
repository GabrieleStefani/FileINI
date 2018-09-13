//
// Created by Lauretta Agliata on 28/08/18.
//

#include "INIManager.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>

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
            }else
                throw std::runtime_error("This file doesn't respect the INI format");
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
    else
        throw NotFoundException("Section not found");
}

void INIManager::changeSectionName(std::string oldName, std::string newName) {
    if(configuration.find(oldName) != configuration.end()){
        std::map<std::string, std::string> params;
        params = *configuration[oldName];
        configuration.insert(make_pair(newName, std::unique_ptr<std::map<std::string, std::string>>(&params)));
        configuration.erase(oldName);
    }
    else
        throw NotFoundException("Section not found");

}

std::map<std::string, std::string> INIManager::getSection(std::string section) {
    if(configuration.find(section) != configuration.end())
        return (*configuration[section]);
    else
        throw NotFoundException("Section not found");
}

void INIManager::addParamToSection(std::string key, std::string value, std::string section) {
    if(configuration.find(section) != configuration.end())
        (*configuration[section])[key] = value;
    else
        throw NotFoundException("Section not found");
}

void INIManager::removeParamFromSection(std::string key, std::string section) {
    if(configuration.find(section) != configuration.end())
        if(configuration[section]->find(key) != configuration[section]->end())
            configuration[section]->erase(key);
        else
            throw NotFoundException("Param not found");
    else
        throw NotFoundException("Section not found");
}

void INIManager::changeParamInSection(std::string key, std::string newValue, std::string section) {
    if(configuration.find(section) != configuration.end())
        if(configuration[section]->find(key) != configuration[section]->end())
            (*configuration[section])[key] = newValue;
        else
            throw NotFoundException("Param not found");
    else
        throw NotFoundException("Section not found");

}

std::string INIManager::getParamValueInSection(std::string key, std::string section) {
    if(configuration.find(section) != configuration.end())
        if(configuration[section]->find(key) != configuration[section]->end())
            return (*configuration[section])[key];
        else
            throw NotFoundException("Param not found");
    else
        throw NotFoundException("Section not found");
}

std::list<std::string> INIManager::findParamSection(std::string key) {
    std::list<std::string> sections;
    for(auto &section : configuration){
        if(section.second->find(key) != section.second->end())
            sections.push_back(section.first);
    }
    if(sections.size() != 0)
        return sections;
    else
        throw NotFoundException("Param not found");
}

void INIManager::addCommentToSection(std::string comment, std::string section) {
    if(configuration.find(section) != configuration.end()) {
        if (comments.find(section) == comments.end())
            comments[section] = comment;
    } else
        throw NotFoundException("Section not found");
}

void INIManager::removeCommentFromSection(std::string section) {
    if(configuration.find(section) != configuration.end()) {
        if (comments.find(section) != comments.end())
            comments.erase(section);
        else
            throw NotFoundException("Comment not found");
    } else
        throw NotFoundException("Section not found");
}

void INIManager::changeCommentInSection(std::string newComment, std::string section) {
    if(configuration.find(section) != configuration.end()) {
        if (comments.find(section) != comments.end())
            comments[section] = newComment;
        else
            throw NotFoundException("Comment not found");
    } else
        throw NotFoundException("Section not found");
}

std::string INIManager::getCommentFromSection(std::string section) {
    if(configuration.find(section) != configuration.end()) {
        if(comments.find(section) != comments.end())
            return comments[section];
        else
            throw NotFoundException("Comment not found");
    } else
        throw NotFoundException("Section not found");
}

