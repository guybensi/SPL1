<<<<<<< HEAD

#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Plan.h"
using std::vector;

//Constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
planId(planId), settlement(settlement), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions), status(PlanStatus::AVALIABLE), life_quality_score(0), economy_score(0), environment_score(0){}

// Copy Constructor
Plan::Plan(const Plan &other): planId(other.planId), facilityOptions(other.facilityOptions), status(other.status), life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score) {
    settlement =  new Settlement (*other.settlement);
    selectionPolicy = other.selectionPolicy->clone();
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
        planId = other.planId;
        status = other.status;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;
        facilityOptions = other.facilityOptions;
        // Dealing with pointers, deleting and reassigning
        delete settlement;
        delete selectionPolicy;
        settlement = new Settlement(*other.settlement); 
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
        return *this; 
    }   
}


const int Plan::getlifeQualityScore() const {return life_quality_score;}

const int Plan::getEconomyScore() const {return economy_score;}

const int Plan::getEnvironmentScore() const {return environment_score;}

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy) {this->selectionPolicy = selectionPolicy;}

void Plan::step(){
    //as long as i can build more
    while (status == PlanStatus::AVALIABLE){
        Facility *selectedFacility = new Facility(this->selectionPolicy->selectFacility(&facilitiesOptions), this->settlement->getName());
        underConstruction.push_back(selectedFacility);
        if (underConstruction.size() == this->settlement->getLimit()){
            this->status = PlanStatus::BUSY; 
        }
    }
    // diung a step for all the facilities
    for (Facility* it = underConstruction.begin(); it != underConstruction.end(); ) {
        (*it).step(); 
    //maybe the facility has finishes building
        if (fac.getStatus() == FacilityStatus::OPERATIONAL) {
            facilities.push_back(it);  
            it = underConstruction.erase(it); 
            Plan::scoreUpdate(it);
        }else {++it;}          
    }
    //maybe the plan can ve avalible
    if (underConstruction.size() < this->settlement->getLimit()) {
        this->status = PlanStatus::AVAILABLE;
}

void Plan::printStatus(){
    if (status == PlanStatus::AVALIABLE) {cout << "plan id: " << plan_id << "settlement: " << settlement <<  "Status: Available" << endl;}
    else {cout << "plan id: " << plan_id << "settlement: " << settlement << "Status: Busy" << endl;}
 }

const vector<Facility*>& Plan::getFacilities() const{return facilities;}

void Plan::addFacility(Facility* facility){ //למה הפונקציה קיימת?
    facilities.push_back(facility);
}

const string Plan::toString() const{
    string result = "PlanID: " + std::to_string(plan_id) + "\n";
    result += "SettlementName: " + settlement->getName() + "\n"; 
    result += "PlanStatus: " + (status == PlanStatus::AVALIABLE ? "AVALIABLE" : "BUSY") + "\n";
    result += "SelectionPolicy: " + selectionPolicy->toString() + "\n"; 
    result += "LifeQualityScore: " + std::to_string(life_quality_score) + "\n";
    result += "EconomyScore: " + std::to_string(economy_score) + "\n";
    result += "EnvironmentScore: " + std::to_string(environment_score) + "\n";
    for (const Facility* facility : facilities) {
        result += "FacilityName: " + facility->toString() + "\n";  
        result += "FacilityStatus: " + (facility->getStatus() == FacilityStatus::UNDER_CONSTRUCTION ? "UNDER_CONSTRUCTION" : "OPERATIONAL") + "\n"; // Assuming Facility has a `getStatus` method
    }
    return result;
}

void Plan::scoreUpdate(Facility* facility) {// our method
    this->life_quality_score = facility->getLifeQualityScore();
    this->economy_score = facility->getEconomyScore();  
    this->environment_score = facility->getEnvironmentScore();  
}

const int Plan::getId(){return plan_id;}// our method

// Destructor
Plan::~Plan() {
    delete settlement;
    delete selectionPolicy;
    for (Facility* facility : underConstruction) {
        delete facility;
    }
    for (Facility* facility : facilities) {
        delete facility;
    }
}


=======

#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Plan.h"
using std::vector;

//Constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
planId(planId), settlement(settlement), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions), status(PlanStatus::AVALIABLE), life_quality_score(0), economy_score(0), environment_score(0){}

// Copy Constructor
Plan::Plan(const Plan &other): planId(other.planId), facilityOptions(other.facilityOptions), status(other.status), life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score) {
    settlement =  new Settlement (*other.settlement);
    selectionPolicy = other.selectionPolicy->clone();
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
        planId = other.planId;
        status = other.status;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;
        facilityOptions = other.facilityOptions;
        // Dealing with pointers, deleting and reassigning
        delete settlement;
        delete selectionPolicy;
        settlement = new Settlement(*other.settlement); 
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
        return *this; 
    }   
}


const int Plan::getlifeQualityScore() const {return life_quality_score;}

const int Plan::getEconomyScore() const {return economy_score;}

const int Plan::getEnvironmentScore() const {return environment_score;}

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy) {this->selectionPolicy = selectionPolicy;}

string Plan::getSelectionPolicy() const {//our method
    if (dynamic_cast<NaiveSelection*>(selectionPolicy)) {
        return "NaiveSelection";
    } else if (dynamic_cast<BalancedSelection*>(selectionPolicy)) {
        return "BalancedSelection";
    } else if (dynamic_cast<EconomySelection*>(selectionPolicy)) {
        return "EconomySelection";
    } else if (dynamic_cast<SustainabilitySelection*>(selectionPolicy)) {
        return "SustainabilitySelection";
    }
}

void Plan::step(){
    //as long as i can build more
    while (status == PlanStatus::AVALIABLE){
        Facility *selectedFacility = new Facility(this->selectionPolicy->selectFacility(&facilitiesOptions), this->settlement->getName());
        underConstruction.push_back(selectedFacility);
        if (underConstruction.size() == this->settlement->getLimit()){
            this->status = PlanStatus::BUSY; 
        }
    }
    // diung a step for all the facilities
    for (Facility* it = underConstruction.begin(); it != underConstruction.end(); ) {
        (*it).step(); 
    //maybe the facility has finishes building
        if (fac.getStatus() == FacilityStatus::OPERATIONAL) {
            facilities.push_back(it);  
            it = underConstruction.erase(it); 
            Plan::scoreUpdate(it);
        }else {++it;}          
    }
    //maybe the plan can ve avalible
    if (underConstruction.size() < this->settlement->getLimit()) {
        this->status = PlanStatus::AVAILABLE;
}

void Plan::printStatus(){
    if (status == PlanStatus::AVALIABLE) {cout << "plan id: " << plan_id << "settlement: " << settlement <<  "Status: Available" << endl;}
    else {cout << "plan id: " << plan_id << "settlement: " << settlement << "Status: Busy" << endl;}
 }

const vector<Facility*>& Plan::getFacilities() const{return facilities;}

void Plan::addFacility(Facility* facility){ //למה הפונקציה קיימת?
    facilities.push_back(facility);
}

const string Plan::toString() const{
    string result = "PlanID: " + std::to_string(plan_id) + "\n";
    if (status == PlanStatus::AVALIABLE){result += "Status: Available";}
    else{result += "Status: Busy";}
    result += "SettlementName: " + settlement->getName() + "\n"; 
    result += "PlanStatus: " + (status == PlanStatus::AVALIABLE ? "AVALIABLE" : "BUSY") + "\n";
    result += "SelectionPolicy: " + selectionPolicy->toString() + "\n"; 
    result += "LifeQualityScore: " + std::to_string(life_quality_score) + "\n";
    result += "EconomyScore: " + std::to_string(economy_score) + "\n";
    result += "EnvironmentScore: " + std::to_string(environment_score) + "\n";
    for (const Facility* facility : facilities) {
        result += "FacilityName: " + facility->toString() + "\n";  
        result += "FacilityStatus: " + (facility->getStatus() == FacilityStatus::UNDER_CONSTRUCTION ? "UNDER_CONSTRUCTION" : "OPERATIONAL") + "\n"; 
    }
    return result;
}

void Plan::scoreUpdate(Facility* facility) {// our method
    this->life_quality_score = facility->getLifeQualityScore();
    this->economy_score = facility->getEconomyScore();  
    this->environment_score = facility->getEnvironmentScore();  
}

const int Plan::getId(){return plan_id;}// our method

// Destructor
Plan::~Plan() {
    delete settlement;//לבדוק האם למחוק באמת
    delete selectionPolicy;
    for (Facility* facility : underConstruction) {
        delete facility;
    }
    for (Facility* facility : facilities) {
        delete facility;
    }
}


>>>>>>> 2353322c569d98d5ed83472974806792ed12caf9
