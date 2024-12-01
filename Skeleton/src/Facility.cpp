
#include <string>
#include <vector>
#include "Facility.h"
using std::string;
using std::vector;

//Constructor
FacilityType ::FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
 name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score){}

const string & FacilityType ::getName() const {return name;}

int FacilityType ::getCost() const {return price;}

int FacilityType ::getLifeQualityScore() const {return lifeQuality_score;}

int FacilityType ::getEnvironmentScore() const {return environment_score;}

int FacilityType ::getEconomyScore() const {return economy_score;}

FacilityCategory FacilityType ::getCategory() const {return category;}




//Constructor
Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score)
    : FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), 
      settlementName(settlementName), 
      status(FacilityStatus::UNDER_CONSTRUCTIONS), 
      timeLeft(price) {}


Facility ::Facility(const FacilityType &type, const string &settlementName):
FacilityType(type), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price){}

const string & Facility ::getSettlementName() const {return settlementName;}

const int Facility ::getTimeLeft() const {return timeLeft;}

FacilityStatus Facility ::step(){
    if(status == FacilityStatus::OPERATIONAL){
        return getStatus();
    }
    timeLeft--;
    if (timeLeft == 0){
        setStatus(FacilityStatus::OPERATIONAL);
        }
    return getStatus();
}

void  Facility ::setStatus(FacilityStatus status){
    switch (status) {
        case FacilityStatus::UNDER_CONSTRUCTIONS:
            this->status = FacilityStatus::UNDER_CONSTRUCTIONS;
            break;
        case FacilityStatus::OPERATIONAL:
            this->status = FacilityStatus::OPERATIONAL;
            break;
    }
}

const FacilityStatus& Facility ::getStatus() const {return status;}

const string Facility ::toString() const{
    string CurrStatus;
    switch (this->status) {
        case FacilityStatus::UNDER_CONSTRUCTIONS:
            CurrStatus = "UNDER_CONSTRUCTIONS";
            break;
        case FacilityStatus::OPERATIONAL:
            CurrStatus = "OPERATIONAL";
            break;
    }
    string CurrCategory;
    switch (this->category) {
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
     return "Name: " + this->name + " | " + 
       "Settlement name: " + this->settlementName + " | " + 
       "Category: " + CurrCategory + " | " + 
       "Status: " + CurrStatus + " | " +
       "Price: " + std::to_string(this->price) + " | " +
       "Life Quality Score: " + std::to_string(this->lifeQuality_score) + " | " +
       "Economy Score: " + std::to_string(this->economy_score) + " | " +
       "Environment Score: " + std::to_string(this->environment_score) + " | " +
       "Time Left: " + std::to_string(this->timeLeft);
}

