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
    for(size_t i=0;i<toSplit.size();i++){
        if(toremovechars.find(toSplit.at(i))!=string::npos){
            if(temp=="")continue;
            splitVec.push_back(trim(temp));
            temp="";
        }else{
            temp+=toSplit.at(i);
        }
    }
    if(temp!="")splitVec.push_back(trim(temp));
    return splitVec;
}


vector<string> split(string toSplit,string splitPoint){
    vector<string> splitVec;
    string temp="";
    for(size_t i=0;i<toSplit.size();i++){
        if(splitPoint.find(toSplit.at(i))!=string::npos){
            if(temp=="")continue;
            splitVec.push_back(trim(temp));
            temp="";
        }else{
            temp+=toSplit.at(i);
        }
    }
    if(temp!="")splitVec.push_back(trim(temp));
    return splitVec;
}

bool isnum(string toConvert){
    string nums="0123456789";
    for(size_t i=0;i<toConvert.size();i++){
        if(nums.find(toConvert.at(i))==string::npos)return false;
    }
    return true;
}
