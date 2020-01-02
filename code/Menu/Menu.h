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

    /// @brief The next menu to be called
    char nextMenu;

    /// @brief The system that the menu will interact with
    System *sys;
public:
    ///@brief Constructs a new menu
    ///@param system The system that the menu will interact with
    Menu(System *system);

    ///@brief Gets Menu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    virtual vector<vector<string>> getOptions() const = 0;

    /// @brief Returns true if the option is valid in the menu that called it
    /// @param option The option that is gonna be verified
    /// @return Returns true if valid and false otherwise
    bool validOption(const string &option) const;

    /// @brief Reads a string from via user input
    /// @return Returns the string read
    string readOption() const;

    /// @brief Reads the input until it's a valid option for the menu that called it
    /// @return Returns the option chosen by the user
    char option() const;

    /// @brief Gets the nextMenu attribute
    /// @return Returns a char representing the next menu that needs to be called
    char getNext() const;
};

///Main menu
class MainMenu : public Menu {
public:
    ///@brief Constructs a new main menu
    ///@param system The system that the menu will interact with
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
class ReadPersonMenu : public ReadMenu<Person> {
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

///@brief Hiring menu
class HireCompaniesMenu : public Menu {
public:
    ///@brief FinanceMenu Constructor
    HireCompaniesMenu(System *system);

    ///@brief Gets FinanceMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

///@brief Employee menu
class EmployeeMenu : public Menu {
public:
    EmployeeMenu(System *system);

    vector<vector<string>> getOptions() const override;
};

class VisitedMuseumsMenu : public Menu {
public:
    ///@brief FinanceMenu Constructor
    VisitedMuseumsMenu(System *system);

    ///@brief Gets FinanceMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

class ReadCompaniesMenu : public Menu {
public:
    ///@brief UpdateMuseumMenu Constructor
    ReadCompaniesMenu(System *system);

    ///@brief Gets UpdateMuseunMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};

class UpdateCompaniesMenu : public Menu {
public:
    ///@brief UpdateMuseumMenu Constructor
    UpdateCompaniesMenu(System *system);

    ///@brief Gets UpdateMuseunMenu in organized manner
    ///@return Returns a matrix(n*2). The first column is a letter representing an option, and the second is the corresponding
    vector<vector<string>> getOptions() const override;
};