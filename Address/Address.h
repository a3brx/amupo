#pragma once

#include <iostream>
#include <string>
#include <utility>
#include "../utils/utils.h"

using namespace std;

class Address{
private:
    string street;
    string postalCode;
    unsigned short doorNumber;
    string locality;
public:
    /// @brief Constructs an Address with the parameters.
    /// @param street The street of the Address.
    /// @param postalCode The postal code of the Address.
    /// @param doorNumber The door number of the Address.
    /// @param locality The local of the Address.
    Address(string street, const string & postalCode, unsigned short doorNumber, string locality);

    Address() = default;
    Address(string addressString);

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
    ///@param street The street to be attributed to the address.
    void setStreet(string street);

    ///@brief Sets the postalCode of the address.
    ///@param postalCode The postal code to be attributed to the address.
    void setPostalCode(string postalCode);

    ///@brief Sets the doorNumber of the address.
    ///@param doorNumber The door number to be attributed to the address.
    void setDoorNumber(unsigned short doorNumber);

    ///@brief Sets the locality of the address.
    ///@param locality The locality to be attributed to the address.
    void setLocality(string locality);


    //operators
    /// @brief Compares two objects of type Date.
    /// @param param The address that is compared with the object.
    /// @return Returns true if two objects of type Date are equal.
    bool operator==(const Address & param) const;
    friend ostream & operator<<(ostream & out, const Address & address);
    friend istream & operator>>(istream & in, Address ** address);

    friend class InvalidAddress;
};

class InvalidAddress : public exception {
public:
    const string street;
    string postalCode;
    unsigned short doorNumber{};
    string locality;
    InvalidAddress() = default;
    explicit InvalidAddress(string street, string postalCode, unsigned short doorNumber, string locality) :
        street(street),
        postalCode(postalCode),
        doorNumber(doorNumber),
        locality(locality) {}
};