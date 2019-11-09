#include "Address.h"


using namespace std;

bool validPostalCode(const string & postalCode){
    vector<string> parts = split(postalCode, "-");
    if(parts.size() != 2)
        return false;
    if(!isnum(parts.at(0)) || !isnum(parts.at(1)))
        return false;
    return !(parts.at(0).size() != 4 || parts.at(1).size() != 3);
}

Address::Address(string street, const string & postalCode, unsigned short doorNumber, string locality) :
    street(move(street)),
    doorNumber(doorNumber),
    locality(move(locality)) {
    if(!validPostalCode(postalCode))
        throw InvalidAddress(street, postalCode, doorNumber, locality);
    this->postalCode = postalCode;
}

Address::Address(string addressString) {
    vector<string> vecStr = trim(split(addressString, ","));
    string auxStreet = vecStr.at(0);
    addressString = vecStr.at(1);
    vecStr = trim(split(addressString, " "));
    unsigned short auxDoor = stoi(vecStr.at(0));
    string auxPostalCode = vecStr.at(1);
    vecStr.erase(vecStr.begin(), vecStr.begin() + 2);
    string auxLocality = join(vecStr);
    *this = Address(auxStreet, auxPostalCode, auxDoor, auxLocality);
}

string Address::getStreet() const{
    return this->street;
}

string Address::getPostalCode() const{
    return this->postalCode;
}

unsigned short Address::getDoorNumber() const{
    return this->doorNumber;
}

string Address::getLocality() const{
    return this->locality;
}

void Address::setStreet(string street){
    this->street = move(street);
}

void Address::setPostalCode(string postalCode){
    if(!validPostalCode(postalCode))
        throw InvalidAddress(this->street, postalCode, this->doorNumber, this->locality);
    this->postalCode = move(postalCode);
}

void Address::setDoorNumber(unsigned short doorNumber){
    this->doorNumber = doorNumber;
}

void Address::setLocality(string locality){
    this->locality = move(locality);
}

bool Address::operator==(const Address& param) const{
    bool res = true;
    res = res && (this->postalCode == param.getPostalCode());
    res = res && (this->doorNumber == param.getDoorNumber());
    return res;
}

ostream & operator<<(ostream & out, const Address & address){
    out << address.street << ", " << address.doorNumber << " " << address.postalCode << " " << address.locality;
    return out;
}

istream & operator>>(istream & in, Address ** address) {
    string aux;
    getline(in,aux);
    *address = new Address(aux);
    return in;
}