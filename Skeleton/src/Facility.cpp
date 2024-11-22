#pragma once
#include <string>
#include <vector>
#include "Fcility.h"
using std::string;
using std::vector;

//Constructor
FacilityType :: FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
 _name(name), category(category), _price(price) {}

FacilityType :: const string &getName() const{return &name}

FacilityType :: int getCost() const{return price}

FacilityType :: int getLifeQualityScore() const{return lifeQuality_score}

FacilityType :: int getEnvironmentScore() const{return environment_score}

FacilityType :: int getEconomyScore() const{return economy_score}

FacilityType :: FacilityCategory getCategory() const {return &category}

//Constructor
Facility :: Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score);

Facility :: Facility(FacilityType &type, const string &settlementName);

Facility :: const string &getSettlementName() const{ return &settlementName }

Facility :: const int getTimeLeft() const{ return timeLeft }

Facility :: FacilityStatus step(){
    timeLeft--;
    if (timeLeft == 0) {setStatus(OPERATIONAL)}// לבדוק אם צריך להוריד את המתקן מאיזה רשימה
}

Facility :: void setStatus(FacilityStatus status){
    switch (status) {
        case FacilityStatus::UNDER_CONSTRUCTIONS:
            status = UNDER_CONSTRUCTIONS;
            break;
        case FacilityStatus::OPERATIONAL:
            typeStr = OPERATIONAL;
            break;
    }
}

Facility :: const FacilityStatus& getStatus() const{ return &status}

Facility :: const string toString() const;//להשלים

