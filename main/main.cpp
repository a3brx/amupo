#include <iostream>
#include <string>
#include "../Address/Address.h"
#include "../Person/Person.h"
#include "../Date/Date.h"
#include "../Event/Event.h"
#include "../Menu/Menu.h"
#include "../Museum/Museum.h"
#include "../System/System.h"
#include "../Table/Table.h"
#include "../utils/utils.h"

using namespace std;

int main(){
    string test="../database/files.txt";
    System sys(test);
    MainMenu m(&sys);
    return 0;
}