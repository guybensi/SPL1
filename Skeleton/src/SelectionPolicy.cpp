#pragma once
#include <vector>
#include "Facility.h"
#include "SelectionPolicy.h"
using std::vector;

//Constructor
NaiveSelection :: NaiveSelection();//מה לשים באינדקס?
NaiveSelection :: const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
NaiveSelection :: const string toString() const override;
NaiveSelection :: NaiveSelection *clone() const override;
NaiveSelection :: ~NaiveSelection() override = default;

//Constructor
BalancedSelection :: BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore): LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore){}

BalancedSelection :: const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override{
    int diff = INT_MAX;
    FacilityType* ans;
    for (currfacility : facilitiesOptions){
        int distancecheck = distance (currfacility)
        if ( distancecheck < diff){
            ans = *currfacility;
            diff = distancecheck;
        } 
    }
    return *ans;
}
BalancedSelection ::int distance (FacilityType CurrFacility){
    int NewLife = this->LifeQualityScore + CurrFacility.getLifeQualityScore;
    int NewEco = this->EconomyScore + CurrFacility.getEconomyScore;
    int NewEnv =this->EnvironmentScore + CurrFacility.getEnvironmentScore;
    return (std::max{NewLife, NewEco, NewEnv}) - (std::min{NewLife, NewEco, NewEnv});
}
BalancedSelection :: const string toString() const override;
BalancedSelection :: BalancedSelection *clone() const override;
BalancedSelection :: ~BalancedSelection() override = default;
    private:
        int LifeQualityScore;
        int EconomyScore;
        int EnvironmentScore;


class EconomySelection: public SelectionPolicy {
    public:
        EconomySelection();
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        EconomySelection *clone() const override;
        ~EconomySelection() override = default;
    private:
        int lastSelectedIndex;

};

class SustainabilitySelection: public SelectionPolicy {
    public:
        SustainabilitySelection();
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        SustainabilitySelection *clone() const override;
        ~SustainabilitySelection() override = default;
    private:
        int lastSelectedIndex;
};