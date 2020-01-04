#pragma once

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

///@brief Company Class
class Company{

    ///@brief Name of the company
    string name;

    ///@brief Contact of the company
    unsigned contact;

    ///@brief Number of repairs the company has done
    unsigned numRepairs;

    ///@brief Position of the company
    pair<double,double> position;
public:

    ///@brief Getter of contact data member.
    ///@return Data member contact.
    unsigned int getContact() const;

    ///@brief Company default constructor
    Company();

    ///@brief Setter of Contact data member
    ///@param contact New contact
    void setContact(unsigned int contact);

    ///@brief Company Constructor
    ///@param name Name of the Company
    ///@param contact Contact of the Company
    ///@param position Position of the Company
    ///@param repairs Repairs done by the Company
    Company(string name, unsigned contact, pair<double, double> position, unsigned repairs = 0);

    ///@brief Getter of the name data member
    ///@return Name of the company
    string getName() const;

    ///@brief Getter of the numRepairs data member
    ///@brief Number of repairs the company has done
    unsigned getNumRepairs() const;

    ///@brief Getter of the position data member
    ///@return Position data member
    pair<double,double> getPosition() const;

    ///@brief Setter of the name data member
    ///@param n New name
    void setName(string n);

    ///@brief Setter of the numRepairs data member
    ///@param numRep New numRepairs
    void setNumRepairs(unsigned numRep);

    ///@brief Setter of the position data member
    ///@param x New x of position data member
    ///@param y New y of position data member
    void setPosition(double x, double y);

    ///@brief Increments numRepairs
    void addRepair();

    ///@brief Auto generates a number of repairs and increments it. Range 1 - 10.
    void generateRepairs();

    ///@brief Relational operator <
    ///@param c1 Company to compare with the calling object
    ///@return true if numRepairs of the object is less than numRepairs of the right hand side of the operator Company.
    bool operator<(const Company& c1) const;

    ///@brief Relational operator ==
    ///@param c1 Company to compare with the calling object
    ///@return true if name of the object is the same name of the right hand side of the operator Company.
    bool operator==(const Company &c1) const;

    ///@brief Relational operator !=
    ///@param c1 Company to compare with the calling object
    ///@return true if the name of the object is not the same as the name of the right hand side of the operator Company.
    bool operator!=(const Company &c1) const;

    ///@brief Input stream operator
    ///@param in Input stream
    ///@param company Double pointer to a company that will be read
    ///@return Input stream without the company info
    friend istream &operator>>(istream &in, Company **company);

    ///@brief Output stream operator
    ///@param on Output stream
    ///@param company Double pointer to a company that will be written
    ///@return Output stream with the company info
    friend ostream &operator<<(ostream &on, Company company);
};