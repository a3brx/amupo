#pragma once
#include "Card.h"

Card::Card(string n,Date aqdate,Date bday,Address ad,unsigned cont): aquisitionDate(aqdate), birthday(bday) {
    name=n;
    address=ad;
    contact=cont;
}

string Card::getName() const{
    return name;
}
Date Card::getAquisitionDate() const{
    return aquisitionDate;
}
Date Card::getBirthday() const{
    return birthday;
}
Address Card::getAdress() const{
    return address;
}
unsigned Card::getContact() const{
    return contact;
}
void Card::setName(string n){
    name=n;
}
void Card::setAddress(Address ad){
    address=ad;
}
void Card::setContact(unsigned cont){
    contact=cont;
}
float SilverCard::getCost(){
    return cost;
}
float UniCard::getCost(){
    return cost;
}
float IndividualCard::getCost(){
    return cost;
}