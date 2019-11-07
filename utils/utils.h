#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

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
///@brief Creates a vector split by the string the user entered.
///@param toSplit String to be separated.
///@return Vector of strings
vector<string> split(string toSplit);
///@brief Creates a vector split by the string the user entered.
///@param toSplit String to be separated.
///@param splitPoint Set of char that decides how the string should be split.
///@return Vector of strings.
vector<string> split(string toSplit,string splitPoint);