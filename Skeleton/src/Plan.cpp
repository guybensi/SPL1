
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
Plan::Plan(const Plan &other):Plan(other.plan_id, other.settlement, other.selectionPolicy->clone(), other.facilityOptions){
    status = other.status;
    life_quality_score = other.getlifeQualityScore();
    economy_score = other.getEconomyScore();
    environment_score = other.getEnvironmentScore();
    for (Facility* facility : other.underConstruction) {
        addFacility(new Facility (*facility));
    }
    for (Facility* facility : other.facilities) {
        addFacility(new Facility (*facility));
    }  
}

// move constractor
Plan::Plan(Plan &&other)
: Plan(other.plan_id, other.settlement, other.selectionPolicy, other.facilityOptions)
{
    status = other.status;
    life_quality_score = other.getlifeQualityScore();
    economy_score = other.getEconomyScore();
    environment_score = other.getEnvironmentScore();

    // Deep copy of the Facility lists (shallow copy of the pointers will lead to issues)
    // Make sure to copy the actual Facility objects and not just the pointers
    facilities.clear();
    for (Facility* facility : other.facilities) {
        addFacility(facility);
    }

    underConstruction.clear();
    for (Facility* facility : other.underConstruction) {
        addFacility(facility);
    }

    // Now reset other object's data after move
    other.facilities.clear(); 
    other.underConstruction.clear();
    other.selectionPolicy = nullptr;  // Since we don't own it, make it nullptr
}

// Move Assignment Operator
Plan& Plan::operator=(Plan &&other) {
    if (this != &other) {
        plan_id = other.plan_id;
        status = other.status;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;
        
        if (selectionPolicy) {
            delete selectionPolicy;
        }
        selectionPolicy = other.selectionPolicy;
        other.selectionPolicy = nullptr;

        facilities.clear();
        for (Facility* facility : other.facilities) {
            addFacility(facility);
        }

        underConstruction.clear();
        for (Facility* facility : other.underConstruction) {
            addFacility(facility);
        }

        other.facilities.clear();
        other.underConstruction.clear();
    }
    return *this;
}



// Copy Assignment Operator
Plan& Plan::operator=(const Plan &other) {
    if (this != &other) {
        plan_id = other.plan_id;
        status = other.status;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;
        if (selectionPolicy) {
            delete selectionPolicy;
        }
        selectionPolicy = (other.selectionPolicy != nullptr) ? other.selectionPolicy->clone() : nullptr;
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

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy) {
    if (this->selectionPolicy != selectionPolicy) {
        delete this->selectionPolicy;
        this->selectionPolicy = selectionPolicy;
    }
}

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
    cout << "step plan" << endl;
    while (status == PlanStatus::AVALIABLE){
        Facility *selectedFacility = new Facility(this->selectionPolicy->selectFacility(facilityOptions),this->settlement.getName());
        addFacility(selectedFacility);
        if (underConstruction.size() == this->settlement.getLimit()){
            this->status = PlanStatus::BUSY; 
        }
    }
    // doing a step for all the facilities
    for (int i = 0; i < underConstruction.size();){
        Facility* currFacility = underConstruction[i];
        FacilityStatus currStat = currFacility->step();
        if (currStat == FacilityStatus::OPERATIONAL){//זה לא נכנס אף פעם משום מש
            cout << "the facility is operational" << endl; 
            addFacility(currFacility);
            scoreUpdate(currFacility);
            underConstruction.erase(underConstruction.begin() + i);
        }
        else{i++;}

    }
    //maybe the plan can be avalible
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
    if(facility->getStatus() == FacilityStatus::OPERATIONAL){
            facilities.push_back(facility);
            cout << "add facility to facilities" << endl;
    }
    else{
        underConstruction.push_back(facility);
        cout << "add facility to under" << endl;
        for (auto *facility : underConstruction){
            cout << facility->getName() << endl;
        }
    }  
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
        result = result +  "Status: Available" + "\n";
    } else {
        result = result + "Status: Busy" + "\n";
    }
    result += "SettlementName: " + settlement.getName() + "\n"; 
    result += "SelectionPolicy: " + selectionPolicy->getName() + "\n"; 
    result += "LifeQualityScore: " + std::to_string(life_quality_score) + "\n";
    result += "EconomyScore: " + std::to_string(economy_score) + "\n";
    result += "EnvironmentScore: " + std::to_string(environment_score) + "\n";
    result += "Under Construction:";
    result +=  "\n";
    for (Facility* facility : underConstruction) {
        result += "FacilityName: " + facility->toString() + "\n";
    }
    result += "\nFacilities:";
    result += "\n";
    for (Facility* facility : facilities) {
        result += "FacilityName: " + facility->toString() + "\n";
    }
    return result;
}


void Plan::scoreUpdate(Facility* facility) {// our method
    this->life_quality_score += facility->getLifeQualityScore();
    this->economy_score += facility->getEconomyScore();  
    this->environment_score += facility->getEnvironmentScore();  
    cout << "score update plan" << endl;
}

const int Plan::getId(){return plan_id;}// our method

// Destructor
Plan::~Plan() {
    if (selectionPolicy != nullptr) {
        delete selectionPolicy;
    }
    for (Facility* facility : underConstruction) {
        delete facility;
    }
    for (Facility* facility : facilities) {
        delete facility;
    }
}


