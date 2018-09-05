//
// Created by Lauretta Agliata on 28/08/18.
//

#include "INIManager.h"
#include <fstream>
#include <sstream>
#include <vector>

std::map<std::string, std::string> INIManager::readFile(std::string fileName) {
    std::map<std::string, std::string> config;

    std::ifstream infile(fileName);
    std::string line;
    while(std::getline(infile, line)){
        std::stringstream linestream(line);
        std::string word;
        std::vector<std::string> wordlist;
        while(std::getline(linestream, word, '=')){
            wordlist.push_back(word);
        }
        if(wordlist.size() == 2)
            config.insert(make_pair(wordlist[0], wordlist[1]));
        else {
            std::cerr<< fileName + " doesn't respect the INI format";
            break;
        }
    }
    return config;
}
