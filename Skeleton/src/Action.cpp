#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
using namespace std;
enum class SettlementType;
enum class FacilityCategory;

//--------------------------------------------------------------------------------------
//Constructor
BaseAction::BaseAction(): errorMsg(""){}
ActionStatus BaseAction::getStatus() const{return status;}
void BaseAction::complete(){status = ActionStatus::COMPLETED;}
void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg; 
}
const string BaseAction::&getErrorMsg() const{return errorMsg;}





//--------------------------------------------------------------------------------------
//Constructor
SimulateStep::SimulateStep(const int numOfSteps):numOfSteps(numOfSteps){}
void SimulateStep::act(Simulation &simulation){
    if (numOfSteps <= 0) {
            error("Invalid number of steps: " + std::to_string(numOfSteps));
            return;
        }
    for (int i = 1; i <= numOfSteps; i++){
        simulation.step();
    }
    complete();
}
const string SimulateStep::toString() const{
    return "SimulateStep: " + std::to_string(numOfSteps) + " steps";
}
SimulateStep* SimulateStep::clone() const{return new SimulateStep(*this);}


//--------------------------------------------------------------------------------------
//Constructor
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):settlementName(settlementName), selectionPolicy(selectionPolicy){}
void AddPlan::act(Simulation &simulation){
    Settlement* settlement = simulation.getSettlement(settlementName);     
    if (settlement == nullptr) {//settlement not found           
        error("Settlement " + settlementName + " not found.");
        return;
        }
    SelectionPolicy* TheSelectionPolicy = simulation.createSelectionPolicy(selectionPolicy);
    if (TheSelectionPolicy == nullptr) {//selection policy not found 
        error("Invalid selection policy: " + selectionPolicy);
        return;
    }
    simulation.addPlan(settlement, TheSelectionPolicy);
    complete();
}
const string AddPlan::toString() const{
            return "AddPlan: Settlement Name = " + settlementName + ", Selection Policy = " + selectionPolicy;
        }
AddPlan* AddPlan::clone() const{return new AddPlan(*this);}





//--------------------------------------------------------------------------------------
//Constructor
AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):settlementName(settlementName), settlementType(settlementType){} 
void AddSettlement::act(Simulation &simulation){
    Settlement* newSettlement = new Settlement(settlementName, SettlementType (settlementType));
    if(!simulation.addSettlement(newSettlement)){
        error("Settlement: " + settlementName +"already exists");
        return;
    }  
    complete();
}
AddSettlement* AddSettlement::clone() const{return new AddSettlement(*this);}
const string AddSettlement::toString() const{
    return "AddSettlement: Settlement Name = " + settlementName + ", Settlement Type = " + settlementTypeToString();
}




//--------------------------------------------------------------------------------------
//Constructor
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
        facilityName(facilityName), facilityCategory(facilityCategory), price(price),lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore){}
void AddFacility::act(Simulation &simulation){
    FacilityType& newFacility = FacilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    if(!simulation.addFacility(newFacility)){
        error("Facility: " + facilityName + "already exists");
        return;
    }
    complete();
}
AddFacility* AddFacility::clone() const{return new AddFacility(*this);}
const string AddFacility::toString() const{
    return "AddFacility: Facility Name = " + facilityName + 
           ", Category = " + std::to_string(static_cast<int>(facilityCategory)) + 
           ", Price = " + std::to_string(price) + 
           ", LifeQualityImpact = " + std::to_string(lifeQualityScore) + 
           ", EconomyImpact = " + std::to_string(economyScore) + 
           ", EnvironmentImpact = " + std::to_string(environmentScore);
}


//--------------------------------------------------------------------------------------
//Constructor
PrintPlanStatus::PrintPlanStatus(int planId):planId(planId){}
void PrintPlanStatus::act(Simulation &simulation){
    if (planId < 0 || planId >= simulation.getplanCounter()) {//the id is not legal
        error("Plan: " + std::to_string(planId) + "doesn't exist");
        return; 
    }
    Plan& plan = simulation.getPlan(planId);  
    cout << plan.toString() << endl;
    complete();
}
PrintPlanStatus* PrintPlanStatus::clone() const{return new PrintPlanStatus(*this);}
const string PrintPlanStatus::toString() const{
    return "PrintPlanStatus: PlanID = " + std::to_string(planId);
}



//--------------------------------------------------------------------------------------
//Constructor

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):planId(planId), newPolicy(newPolicy){}
void ChangePlanPolicy::act(Simulation &simulation){
    if (planId < 0 || planId >= simulation.getplanCounter()) {//the id is not legal
        error("Plan: " + std::to_string(planId) + "doesn't exist");
        return; 
    }
    Plan& plan = simulation.getPlan(planId);
    string currPolicy = plan.getSelectionPolicy();
    if (newPolicy == currPolicy) {
        error("Curr policy and new polic are the same");
        return;
    }
    if (!plan.changePolicy(newPolicy)){
        error("Invalid selection policy");
        return; 
    }
    previousPolicy = currPolicy;
    complete();
}

ChangePlanPolicy* ChangePlanPolicy::clone() const{return new ChangePlanPolicy(*this);}
const string ChangePlanPolicy::toString() const{
    return "ChangePlanPolicy: PlanID = " + std::to_string(planId) + 
           ", Previous Policy = " + previousPolicy + 
           ", New Policy = " + newPolicy;
}

//--------------------------------------------------------------------------------------
class PrintActionsLog : public BaseAction {
    public:
        PrintActionsLog();
        void act(Simulation &simulation) override;
        PrintActionsLog *clone() const override;
        const string toString() const override;
    private:
};
//--------------------------------------------------------------------------------------
class Close : public BaseAction {
    public:
        Close();
        void act(Simulation &simulation) override;
        Close *clone() const override;
        const string toString() const override;
    private:
};
//--------------------------------------------------------------------------------------
class BackupSimulation : public BaseAction {
    public:
        BackupSimulation();
        void act(Simulation &simulation) override;
        BackupSimulation *clone() const override;
        const string toString() const override;
    private:
};

//--------------------------------------------------------------------------------------
class RestoreSimulation : public BaseAction {
    public:
        RestoreSimulation();
        void act(Simulation &simulation) override;
        RestoreSimulation *clone() const override;
        const string toString() const override;
    private:
};