#include "Address.h"


using namespace std;

Address::Address(string street, string postalCode, unsigned short doorNumber, string locality):
    street(move(street)),
    postalCode(move(postalCode)),
    doorNumber(doorNumber),
    locality(move(locality)) {}

Address::Address(string addressString) {
    vector<string> vecStr = trim(split(addressString, ","));
    this->street = vecStr.at(0);
    addressString = vecStr.at(1);
    vecStr = trim(split(addressString, " "));
    this->doorNumber = stoi(vecStr.at(0));
    this->postalCode = vecStr.at(1);
    vecStr.erase(vecStr.begin(), vecStr.begin() + 2);
    this->locality = join(vecStr);
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
    res = res && (this->street == param.getStreet());
    res = res && (this->postalCode == param.getPostalCode());
    res = res && (this->doorNumber == param.getDoorNumber());
    res = res && (this->locality == param.getLocality());
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