#include "Date.h"

using namespace std;

// ----------------------------------------------------------------------------------------------------
//                             Creates a new date equal to the actual date
// ----------------------------------------------------------------------------------------------------
Date::Date() {
    time_t t = time(nullptr);
    year = localtime(&t)->tm_year + 1900;
    month = localtime(&t)->tm_mon + 1;
    day = localtime(&t)->tm_mday;
}

// ----------------------------------------------------------------------------------------------------
//                                Creates a new date in the actual month
// ----------------------------------------------------------------------------------------------------
Date::Date(unsigned char d) {
    time_t t = time(nullptr);
    unsigned short y = localtime(&t)->tm_year + 1900;
    unsigned char m = localtime(&t)->tm_mon + 1;
    if (!validDate(d, m, y))
        throw InvalidDate(d, month, year);
    year = y;
    month = m;
    day = d;
}

// ----------------------------------------------------------------------------------------------------
//                                Creates a new date in the actual year
// ----------------------------------------------------------------------------------------------------
Date::Date(unsigned char d, unsigned char m) {
    time_t t = time(nullptr);
    unsigned short  y = localtime(&t)->tm_year + 1900;
    if (!validDate(d, m, y))
        throw InvalidDate(d, month, year);
    year = y;
    month = m;
    day = d;
}

// ----------------------------------------------------------------------------------------------------
//                                          Creates a new date
// ----------------------------------------------------------------------------------------------------
Date::Date(unsigned char d, unsigned char m, unsigned short y) {
    if (!validDate(d, m, y))
        throw InvalidDate(d, month, year);
    year = y;
    month = m;
    day = d;
}

// ----------------------------------------------------------------------------------------------------
//                      Creates a new date from a string in the format DD-MM-YYYY
// ----------------------------------------------------------------------------------------------------
Date::Date(const string & s) {
    unsigned char d = stoi(s.substr(0, 2));
    unsigned char m = stoi(s.substr(3, 2));
    unsigned short y = stoi(s.substr(6, 4));
    if (!validDate(d, m, y))
        throw InvalidDate(d, month, year);
    year = y;
    month = m;
    day = d;
}

// ----------------------------------------------------------------------------------------------------
//                                       Returns the date's day
// ----------------------------------------------------------------------------------------------------
unsigned char Date::getDay() const {
    return day;
}

// ----------------------------------------------------------------------------------------------------
//                                      Returns the date's month
// ----------------------------------------------------------------------------------------------------
unsigned char Date::getMonth() const {
    return month;
}

// ----------------------------------------------------------------------------------------------------
//                                       Returns the date's year
// ----------------------------------------------------------------------------------------------------
unsigned short Date::getYear() const {
    return year;
}

// ----------------------------------------------------------------------------------------------------
//                                    Sets the date's day if possible
// ----------------------------------------------------------------------------------------------------
void Date::setDay(unsigned char d) {
    if (!validDate(d, month, year))
        throw InvalidDate(d, month, year);
    day = d;
}

// ----------------------------------------------------------------------------------------------------
//                                   Sets the date's month if possible
// ----------------------------------------------------------------------------------------------------
void Date::setMonth(unsigned char m) {
    if (!validDate(day, m, year))
        throw InvalidDate(day, m, year);
    month = m;
}

// ----------------------------------------------------------------------------------------------------
//                                   Sets the date's year if possible
// ----------------------------------------------------------------------------------------------------
void Date::setYear(unsigned short y) {
    if (!validDate(day, month, y))
        throw InvalidDate(day, month, y);
    year = y;
}

// ----------------------------------------------------------------------------------------------------
//                                   Sums a number of days in a date
// ----------------------------------------------------------------------------------------------------
Date Date::operator+(unsigned n) const {
    unsigned res = abs(* this);
    return date(res + n);
}

// ----------------------------------------------------------------------------------------------------
//                               Subtracts a number of days from a date
// ----------------------------------------------------------------------------------------------------
Date Date::operator-(unsigned n) const {
    unsigned res = abs(* this);
    return date(res - n);
}

// ----------------------------------------------------------------------------------------------------
//                             Returns the number of days between two dates
// ----------------------------------------------------------------------------------------------------
int Date::operator-(const Date param) const {
    Date x(day, month, year);
    unsigned actual = abs(x);
    int res = actual - abs(param);
    return res;
}

// ----------------------------------------------------------------------------------------------------
//                                   Sums a number of days in a date
// ----------------------------------------------------------------------------------------------------
void Date::operator+=(unsigned n) {
    unsigned aux = abs(* this);
    Date res = date(aux + n);
    day = res.getDay();
    month = res.getMonth();
    year = res.getYear();
}

// ----------------------------------------------------------------------------------------------------
//                                Subtracts a number of days from a date
// ----------------------------------------------------------------------------------------------------
void Date::operator-=(unsigned n) {
    *this += -(int)n;
}

// ----------------------------------------------------------------------------------------------------
//                        Compares two dates and returns true if they are equal
// ----------------------------------------------------------------------------------------------------
bool Date::operator==(const Date param) const {
    bool res = true;
    res = res && (year == param.getYear());
    res = res && (month == param.getMonth());
    res = res && (day == param.getDay());
    return res;
}

// ----------------------------------------------------------------------------------------------------
//                Compares two dates and returns true if the first is before the second
// ----------------------------------------------------------------------------------------------------
bool Date::operator<(const Date param) const {
    return abs(* this) < abs(param);
}

// ----------------------------------------------------------------------------------------------------
//                  Compares two dates and returns true if the first is after the second
// ----------------------------------------------------------------------------------------------------
bool Date::operator>(const Date param) const {
    return abs(* this) > abs(param);
}

// ----------------------------------------------------------------------------------------------------
//            Compares two dates and returns true if the first is before or equal the second
// ----------------------------------------------------------------------------------------------------
bool Date::operator<=(const Date param) const {
    return abs(* this) <= abs(param);
}

// ----------------------------------------------------------------------------------------------------
//             Compares two dates and returns true if the first is after or equal the second
// ----------------------------------------------------------------------------------------------------
bool Date::operator>=(const Date param) const {
    return abs(* this) >= abs(param);
}

// ----------------------------------------------------------------------------------------------------
//                      Compares two dates and returns true if they are not equal
// ----------------------------------------------------------------------------------------------------
bool Date::operator!= (const Date param) const {
    return !(* this == param);
}

// ----------------------------------------------------------------------------------------------------
//                                  Outputs the date in a nice format
// ----------------------------------------------------------------------------------------------------
ostream& operator<<(ostream & out, const Date & date) {
    out << date.day << "/" << date.month << "/" << date.year;
    return out;
}

// ----------------------------------------------------------------------------------------------------
//                                Returns true if a year is a leap year
// ----------------------------------------------------------------------------------------------------
bool bissextile(unsigned short year) {
    if (year % 4 == 0){
        if (year % 100 != 0 || year % 400 == 0) {
            return true;
        }
    }
    return false;
}

// ----------------------------------------------------------------------------------------------------
//                                   Returns true if a date is valid
// ----------------------------------------------------------------------------------------------------
bool validDate(unsigned char d, unsigned char m, unsigned short y) {
    if (d <= 0 || m <= 0 || y == 0){
        return false;
    }
    if (d == 29 && m == 2){
        return bissextile(y);
    }
    return d <= daysMonth(m);
}

// ----------------------------------------------------------------------------------------------------
//                       Returns the days of a specific month in a non leap year
// ----------------------------------------------------------------------------------------------------
unsigned char daysMonth(unsigned char month) {
    if (month < 8){
        if (month % 2 == 1){
            return 31;
        }else if(month != 2){
            return 30;
        }else{
            return 28;
        }
    } else {
        if (month % 2 == 0){
            return 31;
        }else{
            return 30;
        }
    }
}

// ----------------------------------------------------------------------------------------------------
//                                 Returns the days of a specific year
// ----------------------------------------------------------------------------------------------------
unsigned short daysYear(unsigned short year) {
    if (bissextile(year)){
        return 366;
    }else{
        return 365;
    }
}

// ----------------------------------------------------------------------------------------------------
//                         Returns the number of days of a date since the epoch
// ----------------------------------------------------------------------------------------------------
unsigned abs(const Date date) {
    unsigned short y = date.getYear();
    unsigned char m = date.getMonth();
    unsigned char d = date.getDay();
    unsigned total = 0;
    for (unsigned i = EPOCH; i < y; i++){
        total += daysYear(i);
    }
    for (unsigned i = 1; i < m; ++i){
        total += daysMonth(i);
    }
    if (bissextile(y)){
        total++;
    }
    total += d;
    return total;
}

// ----------------------------------------------------------------------------------------------------
//                   Returns the date that is after a number of days since the epoch
// ----------------------------------------------------------------------------------------------------
Date date(unsigned days) {
    unsigned short y = EPOCH;
    unsigned char m = 1;
    while (days > daysYear(y)){
        days -= daysYear(y++);
    }
    if (days > 31){
        days -= daysMonth(m++);
        if (days > 28){
            if (bissextile(y)){
                days -= daysMonth(m++) + 1;
            }else{
                days -= daysMonth(m++);
            }
            while(days > daysMonth(m)){
                days -= daysMonth(m++);
            }
        }else{
            if (bissextile(y)){
                days--;
            }
        }
    }else{
        if (bissextile(y)){
            days--;
        }
    }
    Date result(days, m, y);
    return result;
}