#include <iostream>
#include "../Address/Address.h"
#include "../Card/Card.h"
#include "../Date/Date.h"
#include "../Event/Event.h"
#include "../Museum/Museum.h"
//#include "System/System.h"
#include "../Table/Table.h"

using namespace std;

int main(){
    vector<string> header = {"Letter", "Option"};
    vector<vector<string>> content = {{"E", "Events Menu"}, {"C", "Clients Menu"}, {"M", "Museums Menu"}, {"Q", "Quit Program"}};
    Table<string> t1(header, content);
    cout << t1 << endl;
    return 0;
}