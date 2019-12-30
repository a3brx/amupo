#pragma once

#include <vector>
#include "../Museum/Museum.h"
#include "binaryTree.h"

using namespace std;

enum field {
    MusName, MusValid, MusAddress, MusCap, MusPos, MusVis
};

class MuseumRegister {

    BST<Museum> museums;
    unsigned sizeBst;
public:
    MuseumRegister(vector<Museum> &mus);

    MuseumRegister();

    BST<Museum> getMuseums();

    bool insert(Museum mus);

    bool remove(Museum mus);

    void updateMuseum(Museum mus, short field, string newVal);

    unsigned size();
};
