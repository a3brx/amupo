#include "Address.h"
#include "../System/System.h"
#include "../utils/utils.h"
#include <utility>


using namespace std;

Address::Address(string st,string pC,unsigned short dN,string local){
    this->street = move(st);
    this->postalCode = move(pC);
    this->doorNumber=dN;
    this->locality = move(local);

}

Address::Address(string adrs) {
//rua nosao, 12 1237-543 Vila Nova de Gaia
    vector<string> vecStr = trim(split(adrs, ","));
    this->street = vecStr.at(0);
    adrs = vecStr.at(1);
    vecStr = trim(split(adrs, " "));
    this->doorNumber = stoi(vecStr.at(0));
    this->postalCode = vecStr.at(1);
    vecStr.erase(vecStr.begin(),++vecStr.begin());
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

void Address::setStreet(string st){
    this->street = move(st);
}

void Address::setPostalCode(string pC){
    this->postalCode=move(pC);
}

void Address::setDoorNumber(unsigned short dN){
    this->doorNumber=dN;
}

void Address::setLocality(string local){
    this->locality=move(local);
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

istream & operator>>(istream & in, Address * address) {
    string aux;
    getline(in,aux);
    address = new Address(aux);
    return in;
}