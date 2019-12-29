#include "registoMuseum.h"
#include <algorithm>

MuseumRegister::MuseumRegister(vector<Museum> mus) : museums(BST<Museum>(Museum())) {
    this->sizeBst = mus.size();
    if (mus.empty()) return;
    sort(mus.begin(), mus.end());
    if (mus.size() % 2 == 1) {
        this->museums.insert(mus.at(mus.size() / 2));
        for (int i = mus.size() / 2 + 1, j = mus.size() / 2 - 1; i < mus.size() && j > 0; i++, j--) {
            this->museums.insert(mus.at(i));
            this->museums.insert(mus.at(j));
        }
    } else {
        for (int i = mus.size() / 2, j = mus.size() / 2 - 1; i < mus.size() && j > 0; i++, j--) {
            this->museums.insert(mus.at(i));
            this->museums.insert(mus.at(j));
        }
    }
    this->museums = this->museums;
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


