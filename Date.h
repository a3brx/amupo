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
    explicit Date(unsigned char d);
    Date(unsigned char d, unsigned char m);
    Date(unsigned char d, unsigned char m, unsigned short y);
    explicit Date(const string & s);
    unsigned char getDay() const;
    unsigned char getMonth() const;
    unsigned short getYear() const;
    void setDay(unsigned char d);
    void setMonth(unsigned char m);
    void setYear(unsigned short y);
    Date operator+(unsigned n) const;
    Date operator-(unsigned n) const;
    int operator-(const Date param) const;
    void operator+=(unsigned n);
    void operator-=(unsigned n);
    bool operator==(const Date param) const;
    bool operator<(const Date param) const;
    bool operator>(const Date param) const;
    bool operator<=(const Date param) const;
    bool operator>=(const Date param) const;
    bool operator!=(const Date param) const;
    friend ostream &operator<<(ostream & out, const Date & date);
};
bool bissextile(unsigned short year);
bool validDate(unsigned char d, unsigned char m, unsigned short y);
unsigned char daysMonth(unsigned char month);
unsigned short daysYear(unsigned short year);
unsigned abs(const Date date);
/// ----------------------------------------------------------------------------------------------------
///                   Returns the date that is after a number of days since the epoch
/// @param days Number of days since the epoch
/// ----------------------------------------------------------------------------------------------------
Date date(unsigned days);

class InvalidDate : exception{
private:
    unsigned char day;
    unsigned char month;
    unsigned short year;
public:
    InvalidDate(unsigned char d, unsigned char m, unsigned short y):
        day(d), month(m), year(y) {};
};