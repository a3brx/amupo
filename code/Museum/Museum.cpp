#include "Museum.h"

#include <utility>

using namespace std;

Museum::Museum(Address adr, pair<double, double> pos, unsigned cap, string name) : address(move(adr)),
                                                                                   position(std::move(pos)),
                                                                                   capacity(cap), name(move(name)) {
}

string Museum::getName() {
    return this->name;
}

Address Museum::getAddress() {
    return this->address;
}

unsigned Museum::getCapacity() {
    return this->capacity;
}

pair<double, double> Museum::getPosition() {
    return this->position;
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

ostream &operator<<(ostream &out, const Museum &museum) {
    out << museum.valid << " | " << museum.name << " | " << museum.position.first << ", " << museum.position.second
        << " | " << museum.capacity << endl << museum.address;
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
    aux.pop_back();
    string auxName = trim(join(aux));
    Address *auxAddress;
    in >> &auxAddress;
    *museum = new Museum(*auxAddress, pos, auxCapacity, auxName);
    (*museum)->valid = valid;
    return in;
}

bool Museum::isValid() const {
    return this->valid;
}

Table<string> toTable(const vector<Museum *> &container) {
    vector<string> header = {"Name", "Capacity", "Address"};
    vector<vector<string>> content;
    for (auto museum : container) {
        stringstream address;
        address << museum->getAddress();
        content.push_back({museum->getName(), to_string(museum->getCapacity()), address.str()});
    }
    Table<string> data(header, content);
    return data;
}