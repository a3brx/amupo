//
// Created by jbr on 27/12/19.
//

#ifndef AMIGO_DOS_MUSEUS_COMPANY_H
#define AMIGO_DOS_MUSEUS_COMPANY_H

#endif //AMIGO_DOS_MUSEUS_COMPANY_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
class Company{
    string name;
    unsigned contact;
    unsigned numRepairs;
    pair<double,double> position;
public:
    unsigned int getContact() const;
    Company();
    void setContact(unsigned int contact);
    Company(string name,unsigned contact,pair<double,double> position);
    string getName() const;
    unsigned getNumRepairs() const;
    pair<double,double> getPosition() const;
    void setName(string n);
    void setNumRepairs(unsigned numRep);
    void setPosition(pair<double,double> newPos);
    void setPosition(double x,double y);
    void addRepair();
    bool operator<(const Company& c1) const;

    friend istream &operator>>(istream &in, Company **company);
    friend ostream &operator<<(ostream &on, Company company);
};