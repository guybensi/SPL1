
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include "Simulation.h"
#include <bits/algorithmfwd.h>
using std::string;
using std::vector;

//Constructor
Simulation::Simulation(const string &configFilePath) : isRunning(false), planCounter(0){//new method******
    // reading from the file
    std::ifstream file(configFilePath);
    if (!file.is_open()) {throw std::runtime_error("Failed to open config file.");}
    string line;
    while (std::getline(file, line)) {
        // if there is # ignore this line
        if (line.empty() || line[0] == '#'){continue;}
        // using the givven class
        std::vector<std::string> arguments = Auxiliary::parseArguments(line);
        if (arguments[0] == "settlement"){//creating a new settlement
            if (arguments.size() != 3){throw std::runtime_error("Invalid settlement format in config file");}
            string name = arguments[1];
            SettlementType type = static_cast<SettlementType>(std::stoi(arguments[2]));
            settlements.push_back(new Settlement(name, type));
        }
        else if (arguments[0] == "facility"){//creating a new facility
            if (arguments.size() != 7){throw std::runtime_error("Invalid facility format in config file");}
            string name = arguments[1];
            FacilityCategory category = static_cast<FacilityCategory>(std::stoi(arguments[2]));
            int price = std::stoi(arguments[3]);
            int lifeQualityScore = std::stoi(arguments[4]);
            int ecoScore = std::stoi(arguments[5]);
            int envScore = std::stoi(arguments[6]);           
            facilitiesOptions.push_back(FacilityType(name, category, price, lifeQualityScore, ecoScore, envScore));
        }
        else if (arguments[0] == "plan"){//creating a new plan
            if (arguments.size() != 3){throw std::runtime_error("Invalid plan format in config file");}
            string settlementName = arguments[1];          
            if (!isSettlementExists (settlementName)){throw std::runtime_error("Settlement not found in plan: " + settlementName);}
            Settlement *settlement = getSettlement(settlementName);
            string policyType = arguments[2];  
            SelectionPolicy *selectionPolicy = nullptr;
            if (policyType == "eco") {
                selectionPolicy = new EconomySelection();
            } else if (policyType == "bal") {
                selectionPolicy = new BalancedSelection(0, 0, 0); // defoult values
            } else if (policyType == "sus") {
                selectionPolicy = new SustainabilitySelection();
            } else {
                throw std::runtime_error("Unknown selection policy: " + policyType);
            }
            addPlan(settlement, selectionPolicy);
        }
    }
    file.close();
}

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

void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy){//********updated function
    std::vector<std::string> validSelectionPolicies = {"nve", "bal", "eco", "env"};
    bool isValidPolicy = std::find(validSelectionPolicies.begin(), validSelectionPolicies.end(), selectionPolicy->getPolicy()) != validSelectionPolicies.end();
    
    if (!isValidPolicy || isSettlementExists(settlement->getName())) {
        throw std::out_of_range("Cannot create this plan");
    }
    plans.push_back(Plan(planCounter++, *settlement, selectionPolicy, facilitiesOptions));
}

void Simulation::addAction(BaseAction *action);

bool Simulation::addSettlement(Settlement *settlement){//********updated function
    if (isSettlementExists(settlement->getName())){throw std::out_of_range("Settlement already exists");}
    Settlement* sett = new (settlement->getName(), settlement->getType()
    settlements.push_back(sett);
    return true;
}
bool Simulation::addFacility(FacilityType facility){//********updated function
    if (isFacilityExists(facility.getName())){throw std::out_of_range("Facility already exists");}
    facilitiesOptions.push_back(facility);
    return true;
}

bool Simulation::isFacilityExists(const string &facilityName){
    for (const FacilityType curr : facilitiesOptions){
        if (curr.getName() == facilityName){return true;}
    }
    return false; 
}

bool Simulation::isSettlementExists(const string &settlementName){
    for (const Settlement* curr : settlements){
        if (curr->getName() == settlementName){return true;}
    }
    return false; 
}

Settlement* Simulation::getSettlement(const string &settlementName){
    for (const Settlement* curr : settlements){
        if (curr->getName() == settlementName){return curr;}
    }
}

Plan &Simulation::getPlan(const int planID){
    for (const Plan& curr : plans){
        if (curr.getId()){ return curr;}
    }
}

void Simulation::step(){//new method******
    open();
    for (Plan p : plans){
        p.step();
    }
    close();
}
void Simulation::close(){//new method******
    for (const Plan& curr : plans){
        cout << curr.toString() << '\n' ;
    }
    isRunning = false;
}

void Simulation::open(){isRunning = true;}//new method******

// Destructor
Simulation:: ~Simulation(){
    for (BaseAction* act : actionsLog){
        delete act;
    }
    for (Settlement *sett : settlements){
        delete sett;
    }
}
