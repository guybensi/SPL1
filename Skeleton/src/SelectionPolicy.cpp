#include <vector>
#include "Facility.h"
#include "SelectionPolicy.h"
#include <algorithm>
#include <initializer_list>
#include <climits>
#include <stdexcept>
using std::vector;

//SelectionPolicy
static SelectionPolicy* SelectionPolicy::createSelectionPolicy(const string& selectionPolicyType){//new method******
    SelectionPolicy* policy = nullptr;
    if (selectionPolicyType == "eco") {
        policy = new EconomySelection();
    } else if (selectionPolicyType == "bal") {
        policy = new BalancedSelection(0, 0, 0);
    } else if (selectionPolicyType == "sus") {
        policy = new SustainabilitySelection();
    } else {
        return 0;
    }
    return policy->clone();// למה לא פשוט להחזיר פוליסה
}

//Constructor
NaiveSelection ::NaiveSelection(): lastSelectedIndex(-1){} 

const FacilityType& NaiveSelection ::selectFacility(const vector<FacilityType>& facilitiesOptions){
 if (facilitiesOptions.empty()) {
        throw std::out_of_range("Vector is empty");
    }
    lastSelectedIndex++;
    return facilitiesOptions[(lastSelectedIndex % facilitiesOptions.size())];
}

const string NaiveSelection ::toString() const{ 
    return "The last selected index was: " + std :: to_string(lastSelectedIndex);
}

 NaiveSelection* NaiveSelection ::clone() const{
    return new NaiveSelection(*this); 
}





//Constructor
BalancedSelection ::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore): LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore){}

const FacilityType& BalancedSelection ::selectFacility(const vector<FacilityType>& facilitiesOptions){
    if (facilitiesOptions.empty()) {
        throw std::runtime_error("No facilities available to select ");} 
    int diff = INT_MAX;
    const FacilityType* ans = nullptr; //לבדוק לגבי קונסט של A
    for (const FacilityType& currfacility : facilitiesOptions){
        int distancecheck = distance (currfacility);
        if ( distancecheck < diff){
            ans = &currfacility;
            diff = distancecheck;
        } 
    }
    LifeQualityScore = LifeQualityScore + ans->getLifeQualityScore;
    EconomyScore = EconomyScore + ans->getEconomyScore;
    EnvironmentScore = EnvironmentScore + ans->getEnvironmentScore;
    return *ans;//לוודא טיפוס החזרה? צריך למחוק אותו? 
}

int BalancedSelection ::distance (const FacilityType &CurrFacility){
    int NewLife = this->LifeQualityScore + CurrFacility.getLifeQualityScore();
    int NewEco = this->EconomyScore + CurrFacility.getEconomyScore();
    int NewEnv = this->EnvironmentScore + CurrFacility.getEnvironmentScore();
    return (std::max({NewLife, NewEco, NewEnv})) - (std::min({NewLife, NewEco, NewEnv}));
}

const string BalancedSelection::toString() const {
    return "Balanced selection with scores: " +
           std::to_string(LifeQualityScore) + ", " +
           std::to_string(EconomyScore) + ", " +
           std::to_string(EnvironmentScore);
}

    
BalancedSelection * BalancedSelection :: clone() const{
    return new BalancedSelection(*this);
}



//Constructor
EconomySelection::EconomySelection(): lastSelectedIndex(-1){}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    for (int i = 1;i<=facilitiesOptions.size(); i++){
        int releventIndex = (lastSelectedIndex + i) % facilitiesOptions.size();
        if (facilitiesOptions[releventIndex].getCategory() == FacilityCategory::ECONOMY) {
            lastSelectedIndex = releventIndex;
            return facilitiesOptions[releventIndex];
        }
    }
     throw std::runtime_error("No eco facility found"); 
}

const string EconomySelection::toString() const {
    return "The last selected index was: " + std::to_string(lastSelectedIndex);
}


EconomySelection * EconomySelection::clone() const{
    return new EconomySelection(*this); 
}





//Constructor
SustainabilitySelection::SustainabilitySelection():lastSelectedIndex(-1){}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
        for (int i = 1;i<=facilitiesOptions.size(); i++){
        int releventIndex = (lastSelectedIndex + i) % facilitiesOptions.size();
        if (facilitiesOptions[releventIndex].getCategory() == FacilityCategory::ENVIRONMENT) {
            lastSelectedIndex = releventIndex;
            return facilitiesOptions[releventIndex];
        }
    }
     throw std::runtime_error("No environment facility found");
}

const string SustainabilitySelection::toString() const{
    return "The last selected index was: " + std :: to_string(lastSelectedIndex);
}

SustainabilitySelection *SustainabilitySelection::clone() const{
    return new SustainabilitySelection(*this);
}


