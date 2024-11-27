#include "Facility.h"
#include <iostream>
#include <cassert>

int main() {
    // יצירת אובייקטים של FacilityType
    FacilityType waterSupply("Water Supply", FacilityCategory::LIFE_QUALITY, 1000, 80, 70, 90);
    FacilityType hospital("Hospital", FacilityCategory::LIFE_QUALITY, 5000, 95, 80, 85);
    FacilityType solarPlant("Solar Plant", FacilityCategory::ENVIRONMENT, 3000, 60, 50, 95);

    // יצירת אובייקטים של Facility
    Facility waterSupplyFacility(waterSupply, "Kfar_SPL");
    Facility hospitalFacility(hospital, "Kiryat_SPL");
    Facility solarPlantFacility(solarPlant, "Mega_SPL");

    // בדיקות ל-FacilityType
    assert(waterSupplyFacility.getName() == "Water Supply");
    assert(waterSupplyFacility.getCategory() == FacilityCategory::LIFE_QUALITY);
    assert(waterSupplyFacility.getCost() == 1000);
    assert(waterSupplyFacility.getLifeQualityScore() == 80);
    assert(waterSupplyFacility.getEconomyScore() == 70);
    assert(waterSupplyFacility.getEnvironmentScore() == 90);

    // בדיקות ל-Facility
    assert(waterSupplyFacility.getSettlementName() == "Kfar_SPL");
    assert(waterSupplyFacility.getTimeLeft() == 1000);

    // בדיקה של פונקציית step
    waterSupplyFacility.step();
    assert(waterSupplyFacility.getTimeLeft() == 999);
    assert(waterSupplyFacility.getStatus() == FacilityStatus::UNDER_CONSTRUCTIONS);

    // בדיקה של שינוי סטטוס אחרי מספר צעדים
    while (waterSupplyFacility.getTimeLeft() > 0) {
        waterSupplyFacility.step();
    }
    assert(waterSupplyFacility.getStatus() == FacilityStatus::OPERATIONAL);

    // אם כל הבדיקות הצליחו
    std::cout << "All tests passed!" << std::endl;

    return 0;
}
