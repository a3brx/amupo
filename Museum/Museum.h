#pragma once

#include <utility>
#include "../Table/Table.h"
#include "../Address/Address.h"
#include "../utils/InvalidInput.h"


using namespace std;

class Museum{
    friend class System;
    private:
    bool valid = true;
    string name;
    Address address;
    unsigned capacity;
    
    public:
    Museum(Address adr, unsigned cap, string name); //verificar nome quando se adiciona ao sistema
                                        //verificar morada ao adiciona
    string getName();
    Address getAddress();
    unsigned getCapacity();
    bool isValid() const;
    void setName(string name);
    void setAddress(Address adr);
    void setCapacity(unsigned cap);

    friend ostream & operator<<(ostream & out, const Museum & museum);
    friend istream & operator>>(istream & in, Museum ** museum);
    template <class T> friend bool compareName(T left, T right);
    friend bool compareCapacity(Museum * left, Museum * right);
};

class ExistingMuseum : public exception, public Museum {
public:
    ExistingMuseum(Museum m) : Museum(m) {}

};

class InvalidMuseum : public exception, public Museum {
public:
    InvalidMuseum(string name, Address add, unsigned cap) : Museum(add, cap, name) {}
};

Table<string> toTable(const vector<Museum *> &container);