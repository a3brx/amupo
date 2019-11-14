#include <iostream>
#include <string>
#include "../Menu/Menu.h"
#include "../System/System.h"


using namespace std;

int main(){
    cout<<"Welcome to the museum manager program!"<<endl;
    cout<<"To start input the login name of your enterprise: ";
    string test;
    getline(cin,test);
    System *sys;
    try {
        sys = new System("../database/"+test+".txt");
    } catch (InvalidInput &error) {
        cout << error.getMsg() << endl;
        return 1;
    }
    try {
        MainMenu m(sys);
    } catch (exception &error) {
        cout << "Error" << endl;
        return 2;
    }
    delete sys;
    return 0;
}

//uni - 140
//ind - 116
//