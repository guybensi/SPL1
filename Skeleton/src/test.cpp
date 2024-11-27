#include <iostream>
#include <cassert>
#include <algorithm>
#include "Facility.h"
#include "SelectionPolicy.h"
#include <vector>

using namespace std;

// פונקציה לחיתוך רווחים מיותרים בסוף ובתחילת מיתר
std::string trim(const std::string &str) {
    std::string result = str;
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), result.end());
    return result;
}

int main() {
    // יצירת אובייקטים של FacilityType
    FacilityType waterSupply("Water Supply", FacilityCategory::LIFE_QUALITY, 1000, 80, 70, 90);
    FacilityType hospital("Hospital", FacilityCategory::LIFE_QUALITY, 5000, 95, 80, 85);
    FacilityType solarPlant("Solar Plant", FacilityCategory::ENVIRONMENT, 3000, 60, 50, 95);
    FacilityType solarPanel("Solar Panel", FacilityCategory::ECONOMY, 1500, 70, 60, 80);

    vector<FacilityType> facilities = {waterSupply, hospital, solarPlant, solarPanel};

    // יצירת אובייקטים של SelectionPolicy
    NaiveSelection naiveSelection;
    EconomySelection economySelection;
    SustainabilitySelection sustainabilitySelection;

    // בדיקות ל-NaiveSelection
    const FacilityType& selectedNaive = naiveSelection.selectFacility(facilities);
    std::cout << "Naive Selection: " << selectedNaive.getName() << std::endl;
    assert(trim(selectedNaive.getName()) == "Water Supply");
    assert(trim(naiveSelection.toString()) == "The last selected index was: 0");

    // בדיקות ל-EconomySelection
    const FacilityType& selectedEconomy = economySelection.selectFacility(facilities);
    std::cout << "Economy Selection: " << selectedEconomy.getName() << std::endl;
    assert(trim(selectedEconomy.getName()) == "Solar Panel");
    assert(trim(economySelection.toString()) == "The last selected index was: 0");

    // בדיקות ל-SustainabilitySelection
    const FacilityType& selectedSustainability = sustainabilitySelection.selectFacility(facilities);
    std::cout << "Sustainability Selection: " << selectedSustainability.getName() << std::endl;
    assert(trim(selectedSustainability.getName()) == "Solar Plant");
    assert(trim(sustainabilitySelection.toString()) == "The last selected index was: 0");

    // אם כל הבדיקות הצליחו
    std::cout << "All tests passed!" << std::endl;

    return 0;
}