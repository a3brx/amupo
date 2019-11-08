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
    Address();

    /// @brief Constructs an Address with the parameters.
    /// @param st The street of the Address.
    /// @param pC The postal code of the Address.
    /// @param dN The door number of the Address.
    /// @param local The local of the Address.
    Address(string st,string pC,unsigned short dN,string local);
    //Address(string postalCode,unsigned short doorNumber); future implementation

    Address(string adrs);

    ///@brief Gets the street of address.
    ///@return The street attribute of the address.
    string getStreet() const;

    ///@brief Gets the postal code of address.
    ///@return The postalCode attribute of the address.
    string getPostalCode() const;

    ///@brief Gets the door number of address.
    ///@return The doorNumber attribute of the address.
    unsigned short getDoorNumber() const;

    ///@brief Gets the locality of address.
    ///@return The locality attribute of the address.
    string getLocality() const;

    ///@brief Sets the street of the address.
    ///@param st The street to be attributed to the address.
    void setStreet(string st);

    ///@brief Sets the postalCode of the address.
    ///@param pC The postal code to be attributed to the address.
    void setPostalCode(string pC);

    ///@brief Sets the doorNumber of the address.
    ///@param dN The door number to be attributed to the address.
    void setDoorNumber(unsigned short dN);

    ///@brief Sets the locality of the address.
    ///@param local The locality to be attributed to the address.
    void setLocality(string local);

    //operators
    /// @brief Compares two objects of type Date.
    /// @param param The address that is compared with the object.
    /// @return Returns true if two objects of type Date are equal.
    bool operator==(const Address& param) const;
    friend ostream & operator<<(ostream & out, const Address & address);
    friend istream & operator>>(istream &in, Address & address);

    friend class InvalidAddress;
};

bool validAddress(Address address);

class InvalidAddress : exception {
public:
    string street;
    string postalCode;
    unsigned short doorNumber{};
    string locality;
    InvalidAddress() = default;
    InvalidAddress(Address ad) : street(ad.street), postalCode(ad.postalCode),
        doorNumber(ad.doorNumber), locality(ad.locality) {}
};