#include "Museum.h"

#include <utility>
#include <stdlib.h>
#include <time.h>

using namespace std;

Museum::Museum(Address adr, pair<double, double> pos, unsigned cap, string name, unsigned vis) : address(move(adr)),
                                                                                                 position(std::move(pos)),
                                                                                                 capacity(cap),
                                                                                                 name(move(name)),
                                                                                                 visits(vis) {
}

string Museum::getName() const {
    return this->name;
}

Address Museum::getAddress() const {
    return this->address;
}

unsigned Museum::getCapacity() const {
    return this->capacity;
}

pair<double, double> Museum::getPosition() const {
    return this->position;
}

unsigned Museum::getVisits() const {
    return this->visits;
}

void Museum::setName(string name) {
    this->name = name;
}

void Museum::setAddress(Address adr) {
    this->address = move(adr);
}

void Museum::setCapacity(unsigned cap) {
    this->capacity = cap;
}

void Museum::setPosition(pair<double, double> pos) {
    this->position = pos;
}

void Museum::setVisits(unsigned vis) {
    this->visits = vis;
}

void Museum::setValid(bool valid) {
    this->valid = valid;
}

ostream &operator<<(ostream &out, const Museum &museum) {
    out << museum.valid << " | " << museum.name << " | " << museum.position.first << ", " << museum.position.second
        << " | " << museum.visits << " | " << museum.capacity << endl << museum.address;
    return out;
}

istream &operator>>(istream &in, Museum **museum) {
    string line;
    getline(in, line);
    if (line.size() == 0) throw InvalidInput();
    vector<string> aux = split(line, "|"), aux2;
    bool valid = (trim(aux.at(0)) == "1");
    pair<double, double> pos;
    aux2 = trim(split(aux.at(2), ","));
    if (aux2.size() != 2) throw InvalidInput();
    pos.first = stod(aux2[0]);
    pos.second = stod(aux2[1]);
    aux.erase(aux.begin());
    if (!isNum(aux.back())) throw InvalidInput();
    unsigned auxCapacity = stoi(aux.back());
    aux.pop_back();
    unsigned visits = stoi(aux.back());
    aux.pop_back();
    aux.pop_back();
    string auxName = trim(join(aux));
    Address *auxAddress;
    in >> &auxAddress;
    *museum = new Museum(*auxAddress, pos, auxCapacity, auxName, visits);
    (*museum)->valid = valid;
    return in;
}

bool Museum::operator<(const Museum rhs) const {
    if (this->visits < rhs.visits) return true;
    if (this->visits == rhs.visits) {
        if (this->name < rhs.name) return true;
    }
    return false;
}

bool Museum::operator==(const Museum rhs) const {
    return this->name == rhs.name;
}

bool Museum::isValid() const {
    return this->valid;
}

void Museum::generateVisits() {
    srand(time(NULL));
    int newVisits = rand() % 30;
    this->visits += newVisits;
}

Table<string> toTable(const vector<Museum *> &container) {
    vector<string> header = {"Valid", "Name", "Capacity", "Address", "Position", "Visits"};
    vector<vector<string>> content;
    for (auto museum : container) {
        stringstream address;
        address << museum->getAddress();
        string validStr;
        if (museum->isValid()) validStr = "Valid";
        else validStr = "Not Valid";
        content.push_back({validStr, museum->getName(), to_string(museum->getCapacity()), address.str(),
                           to_string(museum->getPosition().first) + ", " + to_string(museum->getPosition().second),
                           to_string(museum->getVisits())});
    }
    Table<string> data(header, content);
    return data;
}

bool operator==(const Employee &lhs, const Employee &rhs) {
    bool equal = true;
    equal = (equal && (upper(lhs.getName()) == upper(rhs.getName())));
    equal = (equal && (lhs.getBirthday() == rhs.getBirthday()));
    return equal;
}

bool Employee::isWorking() const {
    return working;
}

void Employee::invalidate() {
    this->working = false;
}

ostream &operator<<(ostream &out, const Employee &employee){
    out << (employee.isWorking() ? "1" : "0") << " ";
    out << employee.getName() << " | ";
    out << employee.getBirthday() << " | ";
    out << employee.getContact() << endl;
    out << employee.getAddress() << endl;
    out << employee.museum->getName();
    return out;
}

istream &operator>>(istream &in, Employee **employee) {
    signed short type;
    in >> type;
    if (in.eof() || type == '\n') throw InvalidInput();
    string aux;
    getline(in, aux);
    Address *ad;
    in >> &ad;
    vector<string> auxvec = trim(split(aux, "|"));
    *employee = new Employee(auxvec.at(0), Date(auxvec.at(1)), *ad, stoi(auxvec.at(2)), nullptr);
    if(!type)
        (*employee)->invalidate();
    return in;
}
