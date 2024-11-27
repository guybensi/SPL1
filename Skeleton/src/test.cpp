#include <iostream>
#include <cassert>
#include "Facility.h"
#include "SelectionPolicy.h"
#include <vector>

using namespace std;

int main() {
    // יצירת אובייקטים של FacilityType
    FacilityType waterSupply("Water Supply", FacilityCategory::LIFE_QUALITY, 1000, 80, 70, 90);
    FacilityType hospital("Hospital", FacilityCategory::LIFE_QUALITY, 5000, 95, 80, 85);
    FacilityType solarPlant("Solar Plant", FacilityCategory::ENVIRONMENT, 3000, 60, 50, 95);
    FacilityType solarPanel("Solar Panel", FacilityCategory::ECONOMY, 1500, 70, 60, 80);

    vector<FacilityType> facilities = {waterSupply, hospital, solarPlant, solarPanel};

    // יצירת אובייקטים של SelectionPolicy
    NaiveSelection naiveSelection;
    BalancedSelection balancedSelection(80, 75, 85);
    EconomySelection economySelection;
    SustainabilitySelection sustainabilitySelection;

    // בדיקות ל-NaiveSelection
    assert(naiveSelection.selectFacility(facilities).getName() == "Water Supply");
    assert(naiveSelection.toString() == "The last selected index was: 0");

    // בדיקות ל-BalancedSelection
    assert(balancedSelection.selectFacility(facilities).getName() == "Solar Plant");
    balancedSelection.setScores(85, 90, 80);
    assert(balancedSelection.toString() == "The last selected index was: 0");

    // בדיקות ל-EconomySelection
    assert(economySelection.selectFacility(facilities).getName() == "Solar Panel");
    assert(economySelection.toString() == "The last selected index was: 0");

    // בדיקות ל-SustainabilitySelection
    assert(sustainabilitySelection.selectFacility(facilities).getName() == "Solar Plant");
    assert(sustainabilitySelection.toString() == "The last selected index was: 0");

    // אם כל הבדיקות הצליחו
    std::cout << "All tests passed!" << std::endl;

    return 0;
}
