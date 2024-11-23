#pragma once
#include <string>
#include <vector>
#include "settlement.h"
using std::string;
using std::vector;

//Constructor
Settelment :: Settlement(const string &name, SettlementType type): _name(name), _type(type){}

//Copy Constructor
//Copy Assignment Operator
//Destructor
Settelment :: const string &getName() const{return &name;}

Settelment :: SettlementType getType() const{return &type;}

Settelment :: const string toString() const{
    string typeStr;
    switch (_type) {
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
    return "Name: " + _name + "\n" + "Type: " + typeStr;
}


