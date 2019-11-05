#include "Address.h"

#include <utility>

Address::Address():doorNumber(0){
    this->street="";
    this->postalCode="0000-000";
    this->locality="";

}
Address::Address(string st,string pC,unsigned short dN,string local){
    this->street = move(st);
    this->postalCode = move(pC);
    this->doorNumber=dN;
    this->locality = move(local);
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
    out<<address.street<<"/"<<address.postalCode<<"/"<<address.doorNumber<<"/"<<address.locality;
    return out;
}





