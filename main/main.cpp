#include <iostream>
#include <string>
#include "../Menu/Menu.h"
#include "../System/System.h"


using namespace std;

int main(){
    cout<<"Welcome to the museum manager program!"<<endl;
    /*cout<<"To start input the login name of your enterprise: ";
    string test,pass;
    getline(cin,test);
    cout<<"Input the password: ";
    getline(cin,pass);*/
    System *sys;
    try {
        sys = new System("../database/files.txt"/*,pass*/);
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
