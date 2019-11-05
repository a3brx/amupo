#pragma once
#include <iostream>
#include <string>

class Menu {
    char current = 'i';
public:
    char read_option() const;
};