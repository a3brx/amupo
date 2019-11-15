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

    bool validOption(const string &option) const;

    string readOption() const;

    char option() const;

    char getNext() const;
};

///Main menu
class MainMenu : public Menu {
public:
    MainMenu(System *system);

    ///@brief Gets MainMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Event menu
class EventMenu : public Menu {
public:
    ///@brief EventMenu Constructor
    EventMenu(System *system);

    ///@brief Gets EventMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Person menu
class PersonMenu : public Menu {
public:
    ///@brief PersonMenu Constructor
    PersonMenu(System *system);

    ///@brief Gets PersonMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Museum menu
class MuseumMenu : public Menu {
public:
    ///@brief MuseumMenu Constructor
    MuseumMenu(System *system);

    ///@brief Gets MuseumMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Update event menu
class UpdateEventMenu : public Menu {
public:
    ///@brief UpdateEventMenu Constructor
    UpdateEventMenu(System *system);

    ///@brief Gets UpdateEventMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Update person menu
class UpdatePersonMenu : public Menu {
public:
    ///@brief UpdatePersonMenu Constructor
    UpdatePersonMenu(System *system);

    ///@brief Gets UpdatePersonMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Update museum menu
class UpdateMuseumMenu : public Menu {
public:
    ///@brief UpdateMuseumMenu Constructor
    UpdateMuseumMenu(System *system);

    ///@brief Gets UpdateMuseunMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Read menu
template<class T>
class ReadMenu : public Menu {
protected:
    ///@brief Vector to be read
    vector<T *> toRead;
public:
    ///@brief ReadMenu Constructor
    explicit ReadMenu(System *system) : Menu(system), toRead({}) {};
};

///@brief Read event menu
class ReadEventMenu : public ReadMenu<Event> {
public:
    ///@brief ReadEventMenu Constructor
    explicit ReadEventMenu(System *system);

    ///@brief Gets ReadEventMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Read person menu
class ReadPersonMenu : public ReadMenu<Client> {
public:
    ///@brief ReadPersonMenu Constructor
    explicit ReadPersonMenu(System *system);

    ///@brief Gets ReadPersonMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Read museum menu
class ReadMuseumMenu : public ReadMenu<Museum> {
public:
    ///@brief ReadMuseumMenu Constructor
    explicit ReadMuseumMenu(System *system);

    ///@brief Gets ReadMuseumMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Finance menu
class FinanceMenu : public Menu {
public:
    ///@brief FinanceMenu Constructor
    FinanceMenu(System *system);

    ///@brief Gets FinanceMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

