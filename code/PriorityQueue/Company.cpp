//
// Created by jbr on 27/12/19.
//

#include "Company.h"
#include "../utils/utils.h"

#include <utility>
#include <vector>

Company::Company(){
    this->position.first=0;
    this->position.second=0;
    this->contact=0;
    this->name="";
    this->numRepairs=0;
}

Company::Company(string name, unsigned contact, pair<double, double> position) {
    this->position=move(position);
    this->contact=contact;
    this->name=move(name);
    this->numRepairs=0;
}

string Company::getName() {
    return name;
}

unsigned Company::getNumRepairs() {
    return numRepairs;
}

pair<double,double> Company::getPosition() const {
    return position;
}

void Company::setName(string n) {
    this->name=move(n);
}

void Company::setNumRepairs(unsigned numRep) {
    this->numRepairs=numRep;
}

void Company::setPosition(pair<double,double> newPos){
    position=move(newPos);
}
void Company::setPosition(double x,double y){
    pair<double,double> temp;
    temp.first=x; temp.second=y;
    position=move(temp);
}

void Company::addRepair() {
    numRepairs++;
}

bool Company::operator<(const Company &c1) const {
    return numRepairs<c1.numRepairs;
}


ostream &operator<<(ostream &on, Company company) {
    on<<company.name<<" | "<<company.contact<<" | "<<company.numRepairs<<" | "<< company.position.first<<" , "<<company.position.second;
    return on;
}

istream &operator>>(istream &in,Company company) {
    string temp;
    getline(in,temp);
    vector<string> vectorTemp=trim(split(temp,"|"));
    company.name=vectorTemp.at(0);
    company.contact=stoul(vectorTemp.at(1));
    company.numRepairs=stoul(vectorTemp.at(2));
    pair<double,double> tempPair;
    tempPair.first=stoul(trim(split(vectorTemp.at(3),",")).at(0));
    tempPair.second=stoul(trim(split(vectorTemp.at(3),",")).at(1));
    company.position=tempPair;
    return in;
}





