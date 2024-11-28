
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include "Simulation.h"
using std::string;
using std::vector;

//Constructor
Simulation::Simulation(const string &configFilePath): isRunning(false)
// Copy Constructor
// Copy Assignment Operator
void Simulation::start();
void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy);
void Simulation::addAction(BaseAction *action);
bool Simulation::addSettlement(Settlement *settlement);
bool Simulation::addFacility(FacilityType facility);
bool Simulation::isSettlementExists(const string &settlementName);

Settlement* Simulation::getSettlement(const string &settlementName){
    for (Settlement* curr : this->settlements){
        if (curr->getName() == settlementName){ return curr;}
    }
}

Plan &Simulation::getPlan(const int planID){
    for (Plan& curr : plans){
        if (curr.getId()){ return curr;}
    }
}

void Simulation::step();
void Simulation::close();
void Simulation::open();
// Destructor
