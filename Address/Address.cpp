#include "Address.h"

#include <utility>

Address::Address():doorNumber(0){
    street="";
    postalCode="0000-000";
    locality="";

}
Address::Address(string st,string pC,unsigned short dN,string local){
    street = move(st);
    postalCode = move(pC);
    doorNumber=dN;
    locality = move(local);
}
string Address::getStreet() const{
    return street;
}
string Address::getPostalCode() const{
    return postalCode;
}
unsigned short Address::getDoorNumber() const{
    return doorNumber;
}
string Address::getLocality() const{
    return locality;
}
void Address::setStreet(string st){
    street = move(st);
}
void Address::setPostalCode(string pC){
    postalCode=move(pC);
}
void Address::setDoorNumber(unsigned short dN){
    doorNumber=dN;
}
void Address::setLocality(string local){
    locality=move(local);
}
bool Address::operator==(const Address& param) const{
    bool res = true;
    res = res && (street == param.getStreet());
    res = res && (postalCode == param.getPostalCode());
    res = res && (doorNumber == param.getDoorNumber());
    res = res && (locality == param.getLocality());
    return res;
}

ostream & operator<<(ostream & out, const Address & address){
    out<<address.street<<"/"<<address.postalCode<<"/"<<address.doorNumber<<"/"<<address.locality;
    return out;
}





