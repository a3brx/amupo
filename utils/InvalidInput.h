#pragma once

#include <string>

class InvalidInput : public std::exception {
private:
    std::string msg;
public:
    InvalidInput(std::string msg) : msg(move(msg)) {};

    std::string getMsg() { return this->msg; }
};
