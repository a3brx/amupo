#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <functional>
using namespace std;

bool clear();

void pause();

///@brief Removes all spaces to the left of the string.
///@param toTrim String to be left trimmed.
///@return String left trimmed.
string ltrim(string toTrim);

///@brief Removes all spaces to the right of the string.
///@param toTrim String to be right trimmed.
///@return String right trimmed.
string rtrim(string toTrim);

///@brief Removes all spaces to the left and to the right of the string.
///@param toTrim String to be trimmed.
///@return String trimmed.
string trim(string toTrim);

///@brief Removes all spaces to the left and to the right of the elements of the vector.
///@param toTrim Vector to have its elements trimmed.
///@return Vector trimmed.
vector<string> trim(vector<string> toTrim);

///@brief Removes all spaces to the left and to the right of the elements of the vector.
///@param toTrim Vector to have its elements trimmed.
void trim(vector<string> *toTrim);

///@brief Creates a vector split by the string the user entered.
///@param toSplit String to be separated.
///@return Vector of strings
vector<string> split(const string& toSplit);

///@brief Creates a vector split by the string the user entered.
///@param toSplit String to be separated.
///@param splitPoint Set of char that decides how the string should be split.
///@return Vector of strings.
vector<string> split(const string& toSplit,const string& splitPoint);

///@brief Recognizes if a string is a number.
///@param toConvert String to check if it's a number.
///@return Returns true if the string is convertible to number;
bool isNum(const string toConvert);

bool isPostalCode(string toTest);

template<class T>
string join(vector<T> vecToJoin, char character = ' ') {
    stringstream res;
    for (auto elem :vecToJoin) {
        res << elem << character;
    }
    return res.str();
}

///@brief Uppercase a string
///@param s String to be uppercase
///@return Uppercased string
string upper(const string & s);

string strPrecision(string num, unsigned decimalDigits = 2);

string getInput(bool (__valid)(string), const string &message = "Choose a option: ", const string &fail = "Invalid input.");

bool isYorN(string toTest);

bool isContact(string toTest);

template<class T, template<class, class = allocator<T>> class Container>
Container<T> filter(const Container<T> &container, bool (filterFunction)(const T &)) {
    Container<T> res;
    for (auto it = container.begin(); it != container.end(); it++)
        if (filterFunction(*it))
            res.push_back(*it);
    return res;
};