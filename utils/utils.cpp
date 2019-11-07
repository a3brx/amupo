#include "utils.h"

string ltrim(string toTrim){
    size_t found=toTrim.find_first_not_of(" ");
    if (found!=string::npos)
    {
        toTrim.substr(found+1);
    }
    return toTrim;
}
string rtrim(string toTrim){
    size_t found=toTrim.find_last_of(" ");
    if (found!=string::npos)
    {
        toTrim.substr(0,found);
    }
    return toTrim;
}
string trim(string toTrim){
    return ltrim(rtrim(toTrim));
}

vector<string> split(string toSplit){
    vector<string> splitVec;
    string toremovechars = " .-_*^`'+&%$#:;,/|=(){}[]?!«»<>";
    for(size_t i;i<toSplit.size();i++){
        if(toremovechars.find(toSplit.at(i))!=string::npos){
            splitVec.push_back(trim(toSplit.substr(0,toSplit.at(i))));
            toSplit=toSplit.substr(toSplit.at(i)+1);
        }
    }
    return splitVec;
}


vector<string> split(string toSplit,string splitPoint){
    vector<string> splitVec;
    for(size_t i;i<toSplit.size();i++){
        if(splitPoint.find(toSplit.at(i))!=string::npos){
            splitVec.push_back(trim(toSplit.substr(0,toSplit.at(i))));
            toSplit=toSplit.substr(toSplit.at(i)+1);
        }
    }
    return splitVec;
}

