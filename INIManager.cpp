//
// Created by Lauretta Agliata on 28/08/18.
//

#include "INIManager.h"
#include <fstream>
#include <sstream>
#include <vector>

void INIManager::readFile(std::string fileName) {
    std::string currentSection = "";

    std::ifstream infile(fileName);
    std::string line;
    int lineNumb = 0;
    while(std::getline(infile, line)){
        lineNumb++;
        if(line.at(0) == '[' && line.back() == ']' && line.size() > 2){
            line = line.substr(1, line.size() - 2);
            configuration.insert(make_pair(line, std::make_unique<std::map<std::string, std::string> *>(new std::map<std::string, std::string>)));
            currentSection = line;
        } else if (line.at(0) == ';' || line.at(0) == '#') {
            comments.insert(make_pair(lineNumb, line.substr(1, line.size())));
        } else {
            std::stringstream lineStream(line);
            std::string word;
            std::vector<std::string> wordList;
            while (std::getline(lineStream, word, '=')) {
                wordList.push_back(word);
            }
            if (wordList.size() == 2) {
                if (currentSection == "")
                    configuration.insert(make_pair(currentSection, std::make_unique<std::map<std::string, std::string> *>(new std::map<std::string, std::string>)));
                (*configuration[currentSection])->insert(make_pair(wordList[0], wordList[1]));
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
    int lineNumb = 1;
    for(auto it = configuration.begin(); it != configuration.end(); it++)
    {
        if(comments.find(lineNumb) != comments.end()){
            outfile << ";" + comments[lineNumb];
            lineNumb++;
        }
        else if(it->first != "") {
            lineNumb++;
            outfile << "[" << it->first << "]" << std::endl;
            for (auto elem : (**(it->second))) {
                lineNumb++;
                outfile << elem.first << "=" << elem.second << std::endl;
            }
        }
    }
    outfile.close();
}

const std::map<std::string, std::unique_ptr<std::map<std::string, std::string> *>> &
INIManager::getConfiguration() const {
    return configuration;
}

