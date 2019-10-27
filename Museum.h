#pragma once
#include "Address.h"

using namespace std;

class Museum{
    private:
    Address address;
    unsigned capacity;
    
    public:
    Museum();
    Museum(Address adr, unsigned cap);

    Address getAddress();
    unsigned getCapacity();
    void setAddress(Address adr);
    void setCapacity(unsigned cap);

    friend ostream & operator<<(ostream & out, const Museum & mus);
};

