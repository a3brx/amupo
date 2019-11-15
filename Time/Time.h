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

    explicit Time(string &str);

    char getHour() const;

    char getMinute() const;

    friend Time operator-(Time left, Time right);
    friend bool operator<(Time left, Time right);
    friend ostream &operator<<(ostream &out, const Time &t);
    friend istream &operator>>(istream &in, Time &t);

    friend bool futureTimeInSameDay(Time time);
};


/// Exception Invalid Time
class InvalidTime : exception {
    char hour;
    char minute;
public:
    InvalidTime(char h, char m) : hour(h), minute(m) {}

    explicit InvalidTime(const string& str) {
        vector<string> aux;
        aux = trim(split(str, ":"));
        if (aux.size() != 2) {
            this->minute = -1;
            this->hour = -1;
        }
        if (!isNum(aux.at(0)) || !isNum(aux.at(1))) {
            this->minute = -1;
            this->hour = -1;
        }
        hour = (char) stoi(aux.at(0));
        minute = (char) stoi(aux.at(1));
    }

    friend ostream &operator<<(ostream &out, InvalidTime &t) {
        out << "The time " << t.hour << ":" << t.minute << " is invalid!";
        return out;
    }
};

bool isTime(const string &str);

bool futureTimeInSameDay(Time time);
