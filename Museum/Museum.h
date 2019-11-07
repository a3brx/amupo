#pragma once
#include "../Address/Address.h"

using namespace std;

class Museum{
    private:
    string name;
    Address address;
    unsigned capacity;
    
    public:
    Museum();
    Museum(Address adr, unsigned cap, string name); //verificar nome quando se adiciona ao sistema
                                        //verificar morada ao adicionar
    string getName();
    Address getAddress();
    unsigned getCapacity();
    void setName(string name);
    void setAddress(Address adr);
    void setCapacity(unsigned cap);

    friend ostream & operator<<(ostream & out, const Museum & mus);
    friend istream & operator>>(istream & in, Museum &museum);
};

