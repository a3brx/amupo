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
    string teste="Teste    *da*'}#Split/Function  .";
    vector<string> vec=split(teste);
    for(int i=0;i<vec.size();i++)
        cout<<vec.at(i)<<endl;
    //MainMenu();
    return 0;
}