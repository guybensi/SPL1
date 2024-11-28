
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include "Simulation.h"
using std::string;
using std::vector;

//Constructor
Simulation::Simulation(const string &configFilePath):planCounter(0){}

// Copy Constructor
Simulation::Simulation(const Simulation &other):isRunning(other.isRunning), planCounter(other.planCounter), plans(other.plans), facilitiesOptions(other.facilitiesOptions){ 
    for (BaseAction* action : other.actionsLog) {
        actionsLog.push_back(action->clone());
    }
    for (Settlement* curr : other.settlements) {
        settlements.push_back(new Settlement(*curr));
    }
}

// Copy Assignment Operator
Simulation& Simulation::operator=(const Simulation &other){ 
    if (this != &other) {
        isRunning = other.isRunning;
        planCounter = other.planCounter;
        facilitiesOptions = other.facilitiesOptions;
        plans = other.plans;
         for (BaseAction* action : actionsLog) {
            delete action;
        }
        actionsLog.clear(); 
        for (BaseAction* action : other.actionsLog) {
            actionsLog.push_back(action->clone());
        } 
         for (Settlement* currSet : settlements) {
            delete currSet;
        }
        settlements.clear(); 
        for (Settlement* currSet : other.settlements) {
            settlements.push_back(new Settlement(*currSet));
        } 
        return *this;   
    } 
}

void Simulation::start();

void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy){
    plans.push_back(Plan(planCounter++, *settlement, selectionPolicy, facilitiesOptions));
}

void Simulation::addAction(BaseAction *action);

bool Simulation::addSettlement(Settlement *settlement){
    if (isSettlementExists(settlement->getName())){return false;}
    settlements.push_back(settlement);
    return true;
}
bool Simulation::addFacility(FacilityType facility){
    if (isFacilityExists(facility.getName())){return false;}
    facilitiesOptions.push_back(facility);
    return true;
}

bool Simulation::isFacilityExists(const string &facilityName){
    for (FacilityType curr : facilitiesOptions){
        if (curr.getName() == facilityName){return true;}
    }
    return false; 
}

bool Simulation::isSettlementExists(const string &settlementName){
    for (Settlement* curr : settlements){
        if (curr->getName() == settlementName){return true;}
    }
    return false; 
}

Settlement* Simulation::getSettlement(const string &settlementName){
    for (Settlement* curr : settlements){
        if (curr->getName() == settlementName){return curr;}
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
Simulation:: ~Simulation(){
    for (BaseAction* act : actionsLog){
        delete act;
    }
    for (Settlement *sett : settlements){
        delete sett;
    }
}
