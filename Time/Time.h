#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "../utils/utils.h"

using namespace std;

class Time {
protected:
    char hour;
    char minute;
public:
    Time();

    Time(char h, char m);

    Time(string str);

    char getHour() const;

    char getMinute() const;

    friend Time operator-(Time &left, Time &right);

    friend istream &operator>>(istream &in, Time &t);
};

class InvalidTime : exception {
    char hour;
    char minute;
public:
    InvalidTime(char h, char m) : hour(h), minute(m) {}

    InvalidTime(string str) {
        vector<string> aux;
        aux = trim(split(str));
        if (aux.size() != 2) {
            this->minute = -1;
            this->hour = -1;
        }
        if (!isNum(aux.at(0)) || !isNum(aux.at(1))) {
            this->minute = -1;
            this->hour = -1;
        }
        hour = stoi(aux.at(0));
        minute = stoi(aux.at(1));
    }

    friend ostream &operator<<(ostream &out, InvalidTime &t) {
        out << "The time " << t.hour << ":" << t.minute << " is invalid!";
    }
};

bool isTime(string str);

