//
// Created by jbr on 27/12/19.
//

#include "Company.h"

#include <utility>


string Company::getName() {
    return name;
}

unsigned Company::getNumRepairs() {
    return numRepairs;
}

void Company::setName(string n) {
    this->name=move(n);
}

void Company::setNumRepairs(unsigned numRep) {
    this->numRepairs=numRep;
}

void Company::addRepair() {
    numRepairs++;
}

bool Company::operator<(const Company &c1) const {
    return numRepairs<c1.numRepairs;
}




