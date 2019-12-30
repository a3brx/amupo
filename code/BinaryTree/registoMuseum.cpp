#include "registoMuseum.h"
#include <algorithm>

MuseumRegister::MuseumRegister(vector<Museum> &mus) : museums(BST<Museum>(Museum())) {
    this->sizeBst = mus.size();
    if (mus.empty()) return;
    sort(mus.begin(), mus.end());
    bool side = false;
    if (mus.size() % 2 == 1) {
        this->museums.insert(mus.at(mus.size() / 2));
        for (int i = mus.size() / 2 + 1, j = mus.size() / 2 - 1; i < mus.size() && j > 0; i++, j--) {
            if (!side) {
                this->museums.insert(mus.at(i));
                this->museums.insert(mus.at(j));
                side = !side;
            } else {
                this->museums.insert(mus.at(j));
                this->museums.insert(mus.at(i));
                side = !side;
            }
        }
    } else {
        for (int i = mus.size() / 2, j = mus.size() / 2 - 1; i < mus.size() && j >= 0; i++, j--) {
            if (!side) {
                this->museums.insert(mus.at(i));
                this->museums.insert(mus.at(j));
                side = !side;
            } else {
                this->museums.insert(mus.at(j));
                this->museums.insert(mus.at(i));
                side = !side;
            }
        }
    }
}

MuseumRegister::MuseumRegister() : museums(BST<Museum>(Museum())) {}

bool MuseumRegister::remove(Museum mus) {
    return this->museums.remove(mus);
}

unsigned MuseumRegister::size() {
    return this->sizeBst;
}

bool MuseumRegister::insert(Museum mus) {
    return this->museums.insert(mus);
}

BST<Museum> MuseumRegister::getMuseums() {
    return this->museums;
}

void MuseumRegister::updateMuseum(Museum mus, short field, string newVal) {
    Museum a = this->museums.find(mus);
    switch (field) {
        case MusName: {
            a.setName(newVal);
            break;
        }
        case MusValid: {
            a.setValid(stoi(newVal));
            break;
        }
        case MusAddress: {
            a.setAddress(Address(newVal));
            break;
        }
        case MusCap: {
            a.setCapacity(stoi(newVal));
            break;
        }
        case MusPos: {
            a.setPosition(strToPair(newVal));
            break;
        }
        case MusVis: {
            a.setVisits(stoi(newVal));
        }
    }
}


