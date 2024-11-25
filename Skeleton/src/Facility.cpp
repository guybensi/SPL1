#pragma once
#include <string>
#include <vector>
#include "Facility.h"
using std::string;
using std::vector;

//Constructor
FacilityType :: FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
 name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score) {}

FacilityType :: const string &getName() const {return &name}

FacilityType :: int getCost() const {return price}

FacilityType :: int getLifeQualityScore() const {return lifeQuality_score}

FacilityType :: int getEnvironmentScore() const {return environment_score}

FacilityType :: int getEconomyScore() const {return economy_score}

FacilityType :: FacilityCategory getCategory() const {return &category}

//Constructor
Facility :: Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
FacilityType(&name, category, price, lifeQuality_score, economy_score, environment_score), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price){}//לבדוק האם ככה צריך לשלוח את השם

Facility :: Facility(const FacilityType &type, const string &settlementName):
FacilityType(type), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price){}//לבדוק האם צריך בנאי מעתיק

Facility :: const string &getSettlementName() const {return &settlementName}

Facility :: const int getTimeLeft() const {return timeLeft}

Facility :: FacilityStatus step(){
    timeLeft--;
    if (timeLeft == 0) {setStatus(OPERATIONAL)}// לבדוק אם צריך להוריד את המתקן מאיזה רשימה
}

Facility :: void setStatus(FacilityStatus status){
    switch (status) {
        case FacilityStatus::UNDER_CONSTRUCTIONS:
            this.status = FacilityStatus::UNDER_CONSTRUCTIONS;
            break;
        case FacilityStatus::OPERATIONAL:
            this.status = FacilityStatus::OPERATIONAL;
            break;
    }
}

Facility :: const FacilityStatus& getStatus() const {return &status}

Facility :: const string toString() const{
    string CurrStatus;
    switch (this.status) {
        case FacilityStatus::UNDER_CONSTRUCTIONS:
            CurrStatus = "UNDER_CONSTRUCTIONS";
            break;
        case FacilityStatus::OPERATIONAL:
            CurrStatus = "OPERATIONAL";
            break;
    }
    string CurrCategory;
    switch (this.category) {
        case FacilityCategory::LIFE_QUALITY:
            CurrCategory = "LIFE_QUALITY";
            break;
        case FacilityCategory::ECONOMY:
            CurrCategory = "ECONOMY";
            break;
        case FacilityCategory::ENVIRONMENT:
            CurrCategory = "ENVIRONMENT";
            break;
    }
     return "Name: " + this.name + " | " + 
       "Settlement name: " + this.settlementName + " | " + 
       "Category: " + CurrCategory + " | " + 
       "Status: " + CurrStatus + " | " +
       "Price: " + std::to_string(this.price) + " | " +
       "Life Quality Score: " + std::to_string(this.lifeQuality_score) + " | " +
       "Economy Score: " + std::to_string(this.economy_score) + " | " +
       "Environment Score: " + std::to_string(this.environment_score) + " | " +
       "Time Left: " + std::to_string(this.timeLeft);
}

