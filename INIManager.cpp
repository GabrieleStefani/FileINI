//
// Created by Lauretta Agliata on 28/08/18.
//

#include "INIManager.h"
#include <fstream>
#include <sstream>
#include <vector>

std::map<std::string, std::unique_ptr<std::map<std::string, std::string>*>> INIManager::readFile(std::string fileName) {
    std::map<std::string, std::unique_ptr<std::map<std::string, std::string>*>> config;

    std::string currentSection = "unknown section";

    std::ifstream infile(fileName);
    std::string line;
    while(std::getline(infile, line)){
        if(line.at(0) == '[' && line.back() == ']' && line.size() > 2){
            line = line.substr(1, line.size() - 2);
            config.insert(make_pair(line, std::make_unique<std::map<std::string, std::string> *>(new std::map<std::string, std::string>)));
            currentSection = line;
        } else if (line.at(0) != ';' && line.at(0) != '#') {
            std::stringstream lineStream(line);
            std::string word;
            std::vector<std::string> wordList;
            while (std::getline(lineStream, word, '=')) {
                wordList.push_back(word);
            }
            if (wordList.size() == 2)
                (*config[currentSection])->insert(make_pair(wordList[0], wordList[1]));
            else {
                std::cerr << fileName + " doesn't respect the INI format";
                break;
            }
        }
    }
    return config;
}
