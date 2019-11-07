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
    string temp="";
    string toremovechars = " .-_*^`'+&%$#:;,/|=(){}[]?!«»<>";
    for(size_t i=0;i<toSplit.size()+1;i++){
        if(toremovechars.find(toSplit.at(i))!=string::npos){
            if(temp=="")continue;
            splitVec.push_back(trim(temp));
            temp="";
        }else{
            temp+=toSplit.at(i);
        }
    }
    return splitVec;
}


vector<string> split(string toSplit,string splitPoint){
    vector<string> splitVec;
    string temp="";
    for(size_t i=0;i<toSplit.size()+1;i++){
        if(splitPoint.find(toSplit.at(i))!=string::npos){
            if(temp=="")continue;
            splitVec.push_back(trim(temp));
            temp="";
        }else{
            temp+=toSplit.at(i);
        }
    }
    return splitVec;
}

