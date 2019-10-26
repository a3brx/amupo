#pragma once
#include <iostream>
#include <string>
using namespace std;
//Teste1
class Address{
    private:
    string street;
    string postalCode;
    unsigned short doorNumber;
    string locality;
    public:
    //Constructor(s)
    Address();
    Address(string st,string pC,unsigned short dN,string local);
    /*Address(string postalCode,unsigned short doorNumber); future implementation*/
    //get methods
    string getStreet() const;
    string getPostalCode() const;
    unsigned short getDoorNumber() const;
    string getLocality() const;
    //set methods
    void setStreet(string st);
    void setPostalCode(string pC);
    void setDoorNumber(unsigned short dN);
    void setLocality(string local);
    //operators
    bool operator==(const Address param) const;
    friend ostream & operator<<(ostream & out, const Address & address);
};