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
    unsigned numRepairs;
    //coords coord;
public:
    string getName();
    unsigned getNumRepairs();
    void setName(string n);
    void setNumRepairs(unsigned numRep);
    void addRepair();
    bool operator<(const Company& c1) const;
};