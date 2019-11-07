#include "Address.h"
#include "../System/System.h"
#include <utility>


using namespace std;

Address::Address(){
    this->street="";
    this->postalCode="0000-000";
    this->doorNumber=0;
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

istream & operator>>(istream &in, Address &address) {
    string aux;
    getline(in,aux);
    unsigned pos = 0;
    pos = aux.find('/');
    address.street = aux.substr(0, pos);
    aux = aux.substr(pos+1);
    pos = aux.find('/');
    address.doorNumber = stoul(aux.substr(0,pos));
    aux = aux.substr(pos+1);
    pos = aux.find('/');
    address.postalCode = aux.substr(0,pos);
    aux = aux.substr(pos+1);
    if(aux.find('/') != string::npos)throw InvalidInput("Address");
    address.locality = aux.substr(0,pos);
    return in;
}

bool validAddress(Address address){
    bool valid= true;
    for(size_t i;i<to_string(address.getDoorNumber()).size();i++)(valid && isdigit(to_string(address.getDoorNumber()).at(i)));
    for(size_t i;i<address.getStreet().size();i++)(valid && (!isdigit(address.getStreet().at(i))));
    for(size_t i;i<address.getLocality().size();i++)(valid && (!isdigit(address.getLocality().at(i))));
    string f4=address.getPostalCode().substr(0,4);
    for(size_t i;i<f4.size();i++)(valid && isdigit(f4.at(i)));
    string s3=address.getPostalCode().substr(5,8);
    for(size_t i;i<s3.size();i++)(valid && isdigit(s3.at(i)));

}


