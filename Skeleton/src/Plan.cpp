
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Plan.h"
#include <iostream>
using namespace std;
using std::vector;

//Constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions), status(PlanStatus::AVALIABLE), life_quality_score(0), economy_score(0), environment_score(0){}

// Copy Constructor
Plan::Plan(const Plan &other):plan_id(other.plan_id), facilityOptions(other.facilityOptions), status(other.status), life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score), settlement(other.settlement), selectionPolicy(other.selectionPolicy->clone()) {
    for (Facility* facility : other.underConstruction) {
        underConstruction.push_back(new Facility (*facility));
    }
    for (Facility* facility : other.facilities) {
        facilities.push_back(new Facility (*facility));
    }  
}

// Copy Assignment Operator
Plan& Plan::operator=(const Plan &other) {
    if (this != &other) {
        plan_id = other.plan_id;
        status = other.status;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;
        delete selectionPolicy;
        selectionPolicy = other.selectionPolicy->clone();  
        for (Facility* facility : underConstruction) {
            delete facility;
        }
        underConstruction.clear(); 
        for (Facility* facility : other.underConstruction) {
            underConstruction.push_back(new Facility(*facility));
        }
        for (Facility* facility : facilities) {
            delete facility;
        }
        facilities.clear();
        for (Facility* facility : other.facilities) {
            facilities.push_back(new Facility(*facility));
        }
    } 
    return *this;   
}


const int Plan::getlifeQualityScore() const {return life_quality_score;}

const int Plan::getEconomyScore() const {return economy_score;}

const int Plan::getEnvironmentScore() const {return environment_score;}

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy) {this->selectionPolicy = selectionPolicy;}

bool Plan::changePolicy(const string newPolicy){//our method
    if (newPolicy == "eco") {
        setSelectionPolicy(new EconomySelection());
        return true; 
    } else if (newPolicy == "env") {
        setSelectionPolicy(new SustainabilitySelection());
        return true;
    } else if (newPolicy == "nve") {
        setSelectionPolicy(new NaiveSelection());
        return true;
    } else if (newPolicy == "bal") {
        int newEcoScore = getEconomyScore();
        int newLifeScore = getlifeQualityScore();
        int newEnvDcore = getEnvironmentScore();
        for (Facility* FcilityUnderConstruction : underConstruction){
            newEcoScore += FcilityUnderConstruction->getEconomyScore();
            newLifeScore += FcilityUnderConstruction->getLifeQualityScore();
            newEnvDcore += FcilityUnderConstruction->getEnvironmentScore();
        }
        setSelectionPolicy (new BalancedSelection (newLifeScore, newEcoScore, newEnvDcore));
        return true;    
    }else {
        return false;
    }
}

string Plan::getSelectionPolicy() const {//our method
    if (dynamic_cast<NaiveSelection*>(selectionPolicy)) {
        return "nve";
    } else if (dynamic_cast<BalancedSelection*>(selectionPolicy)) {
        return "bal";
    } else if (dynamic_cast<EconomySelection*>(selectionPolicy)) {
        return "eco";
    } else if (dynamic_cast<SustainabilitySelection*>(selectionPolicy)) {
        return "env";
    }
}

void Plan::step(){
    //as long as i can build more
    while (status == PlanStatus::AVALIABLE){
        Facility *selectedFacility = new Facility(this->selectionPolicy->selectFacility(facilityOptions),this->settlement.getName());
        underConstruction.push_back(selectedFacility);
        if (underConstruction.size() == this->settlement.getLimit()){
            this->status = PlanStatus::BUSY; 
        }
    }
    // diung a step for all the facilities
    for (auto it = underConstruction.begin(); it != underConstruction.end(); ) {
        (*it)->step(); 
    //maybe the facility has finishes building
        if ((*it)->getStatus() == FacilityStatus::OPERATIONAL) {
            facilities.push_back(*it);  
            it = underConstruction.erase(it); 
            Plan::scoreUpdate(*it);
        }else {++it;}          
    }
    //maybe the plan can ve avalible
    if (underConstruction.size() < this->settlement.getLimit()) {
        this->status = PlanStatus::AVALIABLE;
    }
}

void Plan::printStatus(){
    if (status == PlanStatus::AVALIABLE) {cout << "plan id: " << plan_id << "settlement: " << settlement.getName() <<  "Status: Available" << endl;}
    else {cout << "plan id: " << plan_id << "settlement: " << settlement.getName() << "Status: Busy" << endl;}
 }

const vector<Facility*>& Plan::getFacilities() const{return facilities;}

void Plan::addFacility(Facility* facility){
    facilities.push_back(facility);
}

const string Plan::toString() const {
    string statusString;
    switch (status) {
        case PlanStatus::AVALIABLE:
            statusString =  "AVALIABLE";
            break;
        case PlanStatus::BUSY:
            statusString = "BUSY";
            break;
    }
    string result = "PlanID: " + std::to_string(plan_id) + "\n";
    if (status == PlanStatus::AVALIABLE) {
        result += "Status: Available";
    } else {
        result += "Status: Busy";
    }
    result += "SettlementName: " + settlement.getName() + "\n"; 
    result += "PlanStatus: " + statusString + "\n";
    result += "SelectionPolicy: " + selectionPolicy->toString() + "\n"; 
    result += "LifeQualityScore: " + std::to_string(life_quality_score) + "\n";
    result += "EconomyScore: " + std::to_string(economy_score) + "\n";
    result += "EnvironmentScore: " + std::to_string(environment_score) + "\n";
    for (const Facility* facility : facilities) {
        result += "FacilityName: " + facility->toString() + "\n";
    }
    return result;
}


void Plan::scoreUpdate(Facility* facility) {// our method
    this->life_quality_score += facility->getLifeQualityScore();
    this->economy_score += facility->getEconomyScore();  
    this->environment_score += facility->getEnvironmentScore();  
}

const int Plan::getId(){return plan_id;}// our method

// Destructor
Plan::~Plan() {
    delete selectionPolicy;
    for (Facility* facility : underConstruction) {
        delete facility;
    }
    for (Facility* facility : facilities) {
        delete facility;
    }
}


