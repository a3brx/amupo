//
// Created by jbr on 27/12/19.
//

#ifndef AMIGO_DOS_MUSEUS_AVAILABLECOMPANYS_H
#define AMIGO_DOS_MUSEUS_AVAILABLECOMPANYS_H

#endif //AMIGO_DOS_MUSEUS_AVAILABLECOMPANYS_H

#include <queue>
#include "Company.h"

class AvailableCompanys{
    priority_queue<Company> Companys;
    unsigned numCompanys;
public:
    priority_queue<Company> getCompanys();
    unsigned getNumCompanys();
    void setCompanys(priority_queue<Company> cs);
    void addCompany();
    void addCompany(Company c1);
};
