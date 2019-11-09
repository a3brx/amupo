#include <iostream>
#include <string>
#include "../Menu/Menu.h"
#include "../System/System.h"


using namespace std;

int main(){
    string test="../database/files.txt";
    System sys(test);
    MainMenu m(&sys);
    return 0;
}