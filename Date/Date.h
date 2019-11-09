#pragma once

#include <ctime>
#include <iostream>
#include <vector>
#include <string>

#define EPOCH 1900

using namespace std;

class Date {
private:
    unsigned char day;
    unsigned char month;
    unsigned short year;
public:
    /// @brief Constructs a Date equal to the actual date.
    Date();

    /// @brief Constructs a Date in the actual month.
    /// @param day The day of the Date.
    explicit Date(unsigned char day);

    /// @brief Constructs a Date in the actual year.
    /// @param day The day of the Date.
    /// @param month The month of the Date.
    Date(unsigned char day, unsigned char month);

    /// @brief Constructs a Date with the parameters.
    /// @param day The day of the Date.
    /// @param month The month of the Date.
    /// @param year The year of the Date.
    Date(unsigned char day, unsigned char month, unsigned short year);

    /// @brief Constructs a Date from a string.
    /// @param s A string in the format "DD-MM-YYYY".
    explicit Date(const string & s);

    /// @brief Gets the day of a Date.
    /// @return The day attribute of the Date.
    unsigned char getDay() const;

    /// @brief Gets the month of a Date.
    /// @return The month attribute of the Date.
    unsigned char getMonth() const;

    /// @brief Gets the year of a Date.
    /// @return The year attribute of the Date.
    unsigned short getYear() const;

    /// @brief Sets the day of a Date.
    /// @param day The day to be attributed to the Date.
    void setDay(unsigned char day);

    /// @brief Sets the month of a Date.
    /// @param month The month to be attributed to the Date.
    void setMonth(unsigned char month);

    /// @brief Sets the year of a Date.
    /// @param year The year to be attributed to the Date.
    void setYear(unsigned short year);

    /// @brief Returns a Date that is n days after another.
    /// @param n The number of days after the Date.
    /// @return A Date that is n days after the object.
    Date operator+(unsigned n) const;

    /// @brief Returns a Date that is n days before another.
    /// @param n The number of days before the Date.
    /// @return A Date that is n days before the object.
    Date operator-(unsigned n) const;

    /// @brief Returns the number of days between two Date objects.
    /// @param argument The date that is compared with the object.
    /// @return The number of days between the object and the argument.
    int operator-(const Date argument) const;

    /// @brief Adds a number of days to a Date object.
    /// @param n The number of days to be added to the date.
    void operator+=(unsigned n);

    /// @brief Subtracts a number of days to a Date object.
    /// @param n The number of days to be subtracted from the date.
    void operator-=(unsigned n);

    /// @param param A Date object.
    /// @return Returns true if the param attributes are equal to the object ones, false otherwise.
    bool operator==(const Date param) const;

    /// @param param A Date object.
    /// @return Returns true if the param is before the object, false otherwise.
    bool operator<(const Date param) const;

    /// @param param A Date object.
    /// @return Returns true if the param is after the object, false otherwise.
    bool operator>(const Date param) const;

    /// @param param A Date object.
    /// @return Returns true if the param is before or the same day as the object, false otherwise.
    bool operator<=(const Date param) const;

    /// @param param A Date object.
    /// @return Returns true if the param is after or the same day as the object, false otherwise.
    bool operator>=(const Date param) const;

    /// @param param A Date object.
    /// @return Returns true if the dates are different, false otherwise.
    bool operator!=(const Date param) const;
    friend ostream &operator<<(ostream & out, const Date & date);
    friend istream &operator>>(istream & in, Date & date);
};
bool bissextile(unsigned short year);
bool validDate(unsigned char day, unsigned char month, unsigned short year);
bool validDate(Date d);
unsigned char daysMonth(unsigned char month);
unsigned short daysYear(unsigned short year);
unsigned abs(const Date date);
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
