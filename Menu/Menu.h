#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "../Table/Table.h"

class Menu {
protected:
    char nextMenu;
public:
    Menu();
    virtual vector<vector<string>> getOptions() const = 0;
    bool validOption(const string & option) const;
    string readOption() const;
    char option() const;
    char getNext() const;
};

class MainMenu : public Menu {
public:
    MainMenu();
    vector<vector<string>> getOptions() const override;
};

class EventMenu : public Menu {
public:
    EventMenu();
    vector<vector<string>> getOptions() const override;
};

class ClientMenu : public Menu {
public:
    ClientMenu();
    vector<vector<string>> getOptions() const override;
};

class MuseumMenu : public Menu {
public:
    MuseumMenu();
    vector<vector<string>> getOptions() const override;
};