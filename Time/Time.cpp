#include "Time.h"

using namespace std;

Time::Time() {
    unsigned long t = time(nullptr);
    t %= (24 * 3600);
    hour = t / 3600;
    t %= 3600;
    minute = t / 60;
}

Time::Time(char h, char m) {
    if (h < 0 || h >= 24 || m < 0 || m >= 60) throw InvalidTime(h, m);
    this->hour = h;
    this->minute = m;
}

Time::Time(string str) {
    if (!isTime(str)) throw InvalidTime(str);
    if ()
}

char Time::getHour() const {
    return this->hour;
}

char Time::getMinute() const {
    return this->minute;
}

Time operator-(Time &left, Time &right) {
    signed char resH, resM;
    resM = left.minute - right.minute;
    if (resM < 0) {
        left.hour--;
        resM = 60 + resM;
    }
    resH = left.hour - right.hour;
    if (resH < 0) {
        resH = 24 + resH;
    }
    return Time((char) resH, (char) resM);
}

istream &operator>>(istream &in, Time &t) {
    string timeStr;
    in >> timeStr;
    if (!isTime(timeStr)) throw InvalidTime(timeStr);
    t = Time(timeStr);
}

bool isTime(string str) {
    vector<string> aux;
    aux = trim(split(str));
    if (aux.size() != 2) return false;
    if (!isNum(aux.at(0)) || !isNum(aux.at(1))) return false;
    char h = stoi(aux.at(0)), m = stoi(aux.at(1));
    return (h < 0 || h >= 24 || m < 0 || m >= 60);
}
