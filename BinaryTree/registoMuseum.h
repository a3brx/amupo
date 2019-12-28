#pragma once

#include <vector>
#include "../code/Museum/Museum.h"
#include "binaryTree.h"

using namespace std;

class MuseumRegister {

    BST<Museum> museums;
    unsigned sizeBst;
public:
    MuseumRegister(vector<Museum> mus);

    MuseumRegister();

    bool insert(Museum mus);

    bool remove(Museum mus);

    unsigned size();
};
