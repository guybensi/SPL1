#pragma once
#include <vector>
#include "Facility.h"
#include "SelectionPolicy.h"
#include <algorithm>
#include <initializer_list>
using std::vector;

//Constructor
NaiveSelection ::NaiveSelection(): lastSelectedIndex(-1){} //לוודא בשלושתם

const FacilityType& NaiveSelection ::selectFacility(const vector<FacilityType>& facilitiesOptions) override{
 if (facilitiesOptions.empty()) {
        throw std::out_of_range("Vector is empty");// לבדוק בפורום 
    }
    lastSelectedIndex++;
    return facilitiesOptions[(lastSelectedIndex % facilitiesOptions.size())];
}

const string NaiveSelection ::toString() const override{ // האם צריך להחזיק מתקן ולהחזיר אותו?
    return "The last selected index was: " + std :: to_string(lastSelectedIndex);
}

 NaiveSelection * NaiveSelection ::clone() const override{//מיקום כוכבית? //בנאי מעתיק ששולח בנאי מעתיק?
    return new NaiveSelection(*this); 
}
NaiveSelection :: ~NaiveSelection() override = default;// איך צור במימוש נכון? 




//Constructor
BalancedSelection ::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore): LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore){}

const FacilityType& BalancedSelection ::selectFacility(const vector<FacilityType>& facilitiesOptions) override{
    if (facilitiesOptions.empty()) {
    throw std::runtime_error("No facilities available to select ");} //מותר לזרוק חגירות?
    int diff = INT_MAX;
    FacilityType* ans = nullptr;
    for (FacilityType& currfacility : facilitiesOptions){
        int distancecheck = distance (currfacility);
        if ( distancecheck < diff){
            ans = &currfacility;
            diff = distancecheck;
        } 
    }
    return *ans;//לוודא טיפוס החזרה? צריך למחוק אותו? 
}

int BalancedSelection ::distance (FacilityType &CurrFacility){
    int NewLife = this.LifeQualityScore + CurrFacility.getLifeQualityScore();
    int NewEco = this.EconomyScore + CurrFacility.getEconomyScore();
    int NewEnv = this.EnvironmentScore + CurrFacility.getEnvironmentScore();
    return (std::max({NewLife, NewEco, NewEnv})) - (std::min({NewLife, NewEco, NewEnv}));
}

const string BalancedSelection ::toString() const override{// מה להדפיס?
    
}
BalancedSelection * BalancedSelection :: clone() const override{
    return new BalancedSelection(*this);
}
BalancedSelection :: ~BalancedSelection() override = default;



//Constructor
EconomySelection::EconomySelection(): lastSelectedIndex(-1){}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) override{
    for (int i = 1;i<=facilitiesOptions.size(); i++){
        int releventIndex = (lastSelectedIndex + i) % facilitiesOptions.size();
        if (facilitiesOptions[relventIndex].getCategory() == FacilityCategory::ECONOMY) {
            lastSelectedIndex = releventIndex;
            return facilitiesOptions[relventIndex];
        }
    }
     throw std::runtime_error("No eco facility found"); //לוודא אם מותר לזרוק חריגה
}

const string EconomySelection::toString() const override{
    return "The last selected index was: " + std :: to_string(lastSelectedIndex);
}

EconomySelection * EconomySelection::clone() const override{
    return new EconomySelection(*this); 
}

EconomySelection::~EconomySelection() override = default;



//Constructor
SustainabilitySelection::SustainabilitySelection():lastSelectedIndex(-1){}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) override{
        for (int i = 1;i<=facilitiesOptions.size(); i++){
        int releventIndex = (lastSelectedIndex + i) % facilitiesOptions.size();
        if (facilitiesOptions[relventIndex].getCategory() == FacilityCategory::ENVIRONMENT) {
            lastSelectedIndex = releventIndex;
            return facilitiesOptions[relventIndex];
        }
    }
     throw std::runtime_error("No environment facility found");
}

const string SustainabilitySelection::toString() const override;{
    return "The last selected index was: " + std :: to_string(lastSelectedIndex);
}

SustainabilitySelection *SustainabilitySelection::clone() const override{
    return new EconomySelection(*this); 
}

SustainabilitySelection::~SustainabilitySelection() override = default;