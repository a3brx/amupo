#pragma once

#include <ctime>
#include <iostream>
#include <string>

#define EPOCH 1900

using namespace std;

class Date {
private:
    unsigned char day;
    unsigned char month;
    unsigned short year;
public:
    Date();
    Date(unsigned char d);
    Date(unsigned char d, unsigned char m);
    Date(unsigned char d, unsigned char m, unsigned short y);
    Date(string s);
    unsigned char getDay() const;
    unsigned char getMonth() const;
    unsigned short getYear() const;
    void setDay();
    void setMonth();
    void setYear();
    friend ostream &operator<<(ostream &, const Date &);
    Date operator+(unsigned) const;
    Date operator-(unsigned) const;
    int operator-(const Date) const;
    void operator+=(unsigned);
    void operator-=(unsigned);
    bool operator==(const Date) const;
    bool operator<(const Date) const;
    bool operator>(const Date) const;
    bool operator<=(const Date) const;
    bool operator>=(const Date) const;
    bool operator!=(const Date) const;
}
bool bissextile(unsigned short year);
bool validDate(unsigned char d, unsigned char m, unsigned short y);
unsigned char daysMonth(unsigned char month);
unsigned short daysYear(unsigned short year);
unsigned abs(const Date date);
Date date(unsigned days);