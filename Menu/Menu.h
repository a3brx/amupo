#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include "../Table/Table.h"
#include "../System/System.h"
#include "../Person/Person.h"

///Menu Class
class Menu {
protected:
    friend class System;

    char nextMenu;
    System *sys;
public:
    Menu(System *system);

    virtual vector<vector<string>> getOptions() const = 0;

    bool validOption(const string & option) const;

    string readOption() const;

    char option() const;

    char getNext() const;
};

///Main menu
class MainMenu : public Menu {
public:
    MainMenu(System *system);

    vector<vector<string>> getOptions() const override;
};

////Event menu
class EventMenu : public Menu {
public:
    EventMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

///Person menu
class PersonMenu : public Menu {
public:
    PersonMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

///Museum menu
class MuseumMenu : public Menu {
public:
    MuseumMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

///Update event menu
class UpdateEventMenu : public Menu{
public:
    UpdateEventMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

///Update person menu
class UpdatePersonMenu : public Menu{
public:
    UpdatePersonMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

///Update museum menu
class UpdateMuseumMenu : public Menu{
public:
    UpdateMuseumMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

///Read menu
template<class T>
class ReadMenu : public Menu {
protected:
    vector<T *> toRead;
public:
    explicit ReadMenu(System * system) :
        Menu(system), toRead({}) {};
};

///Read event menu
class ReadEventMenu : public ReadMenu<Event>{
public:
    explicit ReadEventMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

///Read person menu
class ReadPersonMenu : public ReadMenu<Client>{
public:
    explicit ReadPersonMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

///Read museum menu
class ReadMuseumMenu : public ReadMenu<Museum>{
public:
    explicit ReadMuseumMenu(System *system);
    vector<vector<string>> getOptions() const override;
};

///Read finance menu
class FinanceMenu : public Menu {
public:
    FinanceMenu(System *system);

    vector<vector<string>> getOptions() const override;
};

