//
// Created by jbr on 27/12/19.
//

#include "../PriorityQueue/AvailableCompanys.h"

#include <utility>

priority_queue<Company> AvailableCompanys::getCompanys() {
    return Companys;
}

unsigned AvailableCompanys::getNumCompanys() {
    return Companys.size();
}

void AvailableCompanys::setCompanys(priority_queue<Company> cs) {
    this->Companys=move(cs);
}

void AvailableCompanys::addCompany() {

}

void AvailableCompanys::addCompany(Company c1) {
    this->Companys.push(c1);
}
