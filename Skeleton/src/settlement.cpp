#pragma once
#include <string>
#include <vector>
#include "Settlement.h"
using std::string;
using std::vector;

//Constructor
Settlement ::Settlement(const string &name, SettlementType type): name(name), type(type){}

const string& Settlement ::getName() const{return &name;}

SettlementType Settlement ::getType() const{return &type;}

const string Settlement ::toString() const{
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
