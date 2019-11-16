#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "../utils/utils.h"

using namespace std;

/// @brief The Address class
class Address {
private:
    /// @brief The street of the address
    string street;
    /// @brief The postal code of the address
    string postalCode;
    /// @brief The door number of the address
    unsigned short doorNumber;
    /// @brief The locality of the address
    string locality;
public:
    /// @brief Constructs an Address with the parameters.
    /// @param street The street of the Address.
    /// @param postalCode The postal code of the Address.
    /// @param doorNumber The door number of the Address.
    /// @param locality The local of the Address.
    Address(string street, const string &postalCode, unsigned short doorNumber, string locality);

    /// @brief Constructs an Address with the default parameters.
    Address() = default;

    /// @brief Constructs an Address from a string.
    /// @param addressString The address in a string format.
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
    bool operator==(const Address &param) const;

    /// @brief Sends a address to a ostream object.
    /// @param out The ostream object to where we are gonna send the Address information.
    /// @param address The address that is send.
    /// @return Returns the ostream itself.
    friend ostream &operator<<(ostream &out, const Address &address);

    /// @brief Reads a address from a istream object.
    /// @param in The istream object where the information to create the new address is.
    /// @param address A pointer to a pointer that is gonna point to the new Address.
    /// @return Returns the istream itself.
    friend istream &operator>>(istream &in, Address **address);

    friend class InvalidAddress;
};

///@brief Exception Invalid Address
class InvalidAddress : public exception, public Address {
public:
    /// @brief Constructs a new InvalidAddress exception with default attributes
    InvalidAddress() = default;

    /// @brief Constructs a new InvalidAddress exception
    /// @param street The street of the Invalid Address
    /// @param postalCode The postal code of the Invalid Address
    /// @param doorNumber The number of the Invalid Address
    /// @param locality The locality of the Invalid Address
    explicit InvalidAddress(string street, string postalCode, unsigned short doorNumber, string locality) : Address(
            street, postalCode, doorNumber, locality) {}
};