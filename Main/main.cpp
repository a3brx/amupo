#include <iostream>
#include "../Address/Address.h"
#include "../Card/Card.h"
#include "../Date/Date.h"
#include "../Event/Event.h"
#include "../Menu/Menu.h"
#include "../Museum/Museum.h"
//#include "System/System.h"
#include "../Table/Table.h"
#include "../utils/utils.h"

using namespace std;

int main(){
    string teste="ola*eu$  sou muito #+fixe";
    vector<string> vec=split(teste);
    for(int i=0;i<vec.size();i++)
        cout<<vec.at(i);
    //MainMenu();
    return 0;
}