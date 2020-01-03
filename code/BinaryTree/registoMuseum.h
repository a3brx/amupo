#pragma once

#include <vector>
#include "../Museum/Museum.h"
#include "binaryTree.h"

using namespace std;

enum field {
    MusName, MusValid, MusAddress, MusCap, MusPos, MusVis
};

///@brief Register of Museums. Works with BST
class MuseumRegister {

    ///@brief BST of valid and visited Museums
    BST<Museum> museums;

    ///@brief sizeBST Size of the BST
    unsigned sizeBst;
public:

    ///@brief MuseumRegister Constructor. Makes a balanced BST.
    MuseumRegister(vector<Museum> &mus);

    ///@brief MuseumRegister default Constructor.
    MuseumRegister();

    ///@brief Gets the BST of Museums.
    ///@return BST of valid and visited Museums.
    BST<Museum> getMuseums();

    ///@brief Inserts a Museum in the BST
    ///@param mus Museum to be inserted
    ///@return True if successful, false otherwise
    bool insert(Museum mus);

    ///@brief Removes a Museum from the BST
    ///@param mus Museum to be removed
    ///@return True if successful, false otherwise
    bool remove(Museum mus);

    ///@brief Updates a Museum in the BST.
    ///@param mus Museum to update.
    ///@param field Museum's field to update.
    ///@param newVal Updated Value
    void updateMuseum(Museum mus, short field, string newVal);

    ///@brief Gets the size of the BST
    ///@return The size of the BST.
    unsigned size();
};
