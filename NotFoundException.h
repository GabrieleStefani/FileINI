//
// Created by Lauretta Agliata on 13/09/18.
//

#ifndef FILEINI_NOTFOUNDEXCEPTION_H
#define FILEINI_NOTFOUNDEXCEPTION_H

#include <exception>
#include <string>

class NotFoundException : public std::logic_error{
public:
    NotFoundException(const std::string message = "") : std::logic_error(message.c_str()){}
};


#endif //FILEINI_NOTFOUNDEXCEPTION_H
