#pragma once

#include <utility>
#include "../Table/Table.h"
#include "../Address/Address.h"
#include "../Person/Person.h"
#include "../utils/InvalidInput.h"

using namespace std;

///@brief Museum Class
class Museum {
    friend class System;

    /// @brief True if the museum is active on the system
    bool valid = true;

    /// @brief The name of the museum
    string name;

    /// @brief The address of the museum
    Address address;

    /// @brief The capacity of the museum
    unsigned capacity;

    pair<double, double> position;

    unsigned visits;

public:
    ///@brief Contructs a Museum
    ///@param adr Address of the museum
    ///@param cap Capacity of the museum
    ///@param name Name of the museum
    Museum(Address adr, pair<double, double> pos, unsigned cap, string name, unsigned vis = 0);

    Museum() : position({360, 360}) {}

    ///@brief Gets the museum name
    ///@return Returns the name of the Musuem
    string getName() const;

    ///@brief Gets the museum address
    ///@return Returns the address of the Musuem
    Address getAddress() const;

    ///@brief Gets the museum capacity
    ///@return Returns the capacity of the Musuem
    unsigned getCapacity() const;

    pair<double, double> getPosition() const;

    unsigned getVisits() const;

    /// @brief Verifies if a museum is active in the system
    /// @return Returns true if the museum is valid
    bool isValid() const;

    /// @brief Sets the name of the museum
    /// @param name The new name of the museum
    void setName(string name);

    /// @brief Sets the address of the museum
    /// @param adr The new address of the museum
    void setAddress(Address adr);

    /// @brief Sets the capacity of the museum
    /// @param cap The new capacity of the museum
    void setCapacity(unsigned cap);

    void setPosition(pair<double, double> pos);

    void setVisits(unsigned vis);

    void setValid(bool valid);

    void generateVisits();

    /// @brief Sends a museum information to a ostream object
    /// @param out The ostream object to where the museum information is gonna be send
    /// @param museum The museum object that is gonna be printed on the ostream object
    /// @return Returns the ostream itself
    friend ostream &operator<<(ostream &out, const Museum &museum);

    /// @brief Creates a new museum from a istream
    /// @param in A istream object from where the information of the museum is gonna be acquired
    /// @param museum A pointer to a pointer of museum, that will point to the new museum created inside the function
    /// @return Returns the istream itself
    friend istream &operator>>(istream &in, Museum **museum);

    bool operator<(const Museum rhs) const;

    bool operator==(const Museum rhs) const;

    template<class T>
    friend bool compareName(T left, T right);

    /// @brief Compares the capacities of two museums
    /// @param left The first museum to be tested
    /// @param right The second museum to be tested
    /// @return Returns true if the capacities of the museums are equal
    friend bool compareCapacity(Museum *left, Museum *right);


};

///@brief The Employee Class
class Employee : public Person {
    /// @brief The state of the employee, true is it's working in a museum
    bool working = true;
public:
    /// @brief The memory address of the Museum where the employee works, NULL if they are not working
    Museum *museum;

    /// @return Returns true if the object is employed in the museum
    bool isWorking() const;

    /// @brief Sets the working attribute to false
    void invalidate();

    /// @brief Constructs a new Employee from the arguments
    /// @param name The name of the new Employee
    /// @param birthday The birthday of the new Employee
    /// @param address The Address of the new Employee
    /// @param contact The contact of the new Employee
    /// @param museum The memory address of the Museum where the employee works
    Employee(string name, Date birthday, Address address, unsigned contact, Museum *museum) : Person(name, birthday, address, contact) {
        this->museum = museum;
    };

    /// @brief Compares two Employee objects
    /// @param lhs The first Employee that will be compared
    /// @param rhs The second Employee that will be compared
    /// @return Returns true if both arguments have the same name and birthday
    friend bool operator==(const Employee &lhs, const Employee &rhs);

    /// @brief Sends a employee information to a ostream object
    /// @param out The ostream object to where the employee information is gonna be send
    /// @param employee The employee object that is gonna be printed on the ostream object
    /// @return Returns the ostream itself
    friend ostream &operator<<(ostream &out, const Employee &employee);

    /// @brief Creates a new employee from a istream
    /// @param in A istream object from where the information of the employee is gonna be acquired
    /// @param employee A pointer to a pointer of employee, that will point to the new employee created inside the function
    /// @return Returns the istream itself
    friend istream &operator>>(istream &in, Employee **employee);
};

/// @brief The struct that will be passed as template to the hash table of employees
struct employeeHash {
    /// @brief The hash table of the Employee Hash Table, that returns the contact of the employee
    int operator()(const Employee* employee) const {
        return (int) employee->getContact();
    }

    /// @brief The equality operator of the Employee Hash Table
    bool operator()(const Employee* left, const Employee* right) const {
        return *left == *right;
    }
};

/// @brief Existing Museum Exception
class ExistingMuseum : public exception, public Museum {
public:
    /// @brief Constructs an ExistingMuseum exception
    /// @param m The Museum that already exists
    ExistingMuseum(Museum m) : Museum(m) {}

};

/// @brief invalid Museum ExceptiontoTable
class InvalidMuseum : public exception {
private:
    ///@brief Supposed address of the invalid museum
    Address address;
    ///@brief Supposed capacity of the invalid museum
    unsigned capacity;
    ///@brief Supposed name of the invalid museum
    string name;
public:
    /// @brief Constructs an InvalidMuseum exception
    /// @param name The name of the supposed museum
    /// @param add The address of the supposed museum
    /// @param cap The capacity of the supposed museum
    InvalidMuseum(string name, Address add, unsigned cap) : address(add), capacity(cap), name(name) {}
};

/// @brief Creates a Table from museums
/// @param container A vector of pointers to Museums
/// @return A table made from the museums information
Table<string> toTable(const vector<Museum *> &container);