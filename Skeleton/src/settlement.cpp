#pragma once
#include <string>
#include <vector>
#include "Settlement.h"
using std::string;
using std::vector;

//Constructor
Settlement :: Settlement(const string &name, SettlementType type): name(name), type(type){}

//Copy Constructor (no need)
//Copy Assignment Operator
//Destructor
Settlement :: const string &getName() const{return &name;}

Settlement :: SettlementType getType() const{return &type;}

Settlement :: const string toString() const{
    string typeStr;
    switch (type) {
        case SettlementType::VILLAGE:
            typeStr = "Village";
            break;
        case SettlementType::CITY:
            typeStr = "City";
            break;
        case SettlementType::METROPOLIS:
            typeStr = "Metropolis";
            break;
    }
    return "Name: " + name + " " + "Type: " + typeStr;
}


