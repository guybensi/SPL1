#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
enum class SettlementType;
enum class FacilityCategory;

//Constructor
BaseAction::BaseAction(): errorMsg(""){}
ActionStatus BaseAction::getStatus() const{return status;}
void BaseAction::complete(){status = ActionStatus::COMPLETED;}
void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg; 
}
const string BaseAction::&getErrorMsg() const{return errorMsg;}






//Constructor
SimulateStep::SimulateStep(const int numOfSteps):numOfSteps(numOfSteps){}
void SimulateStep::act(Simulation &simulation) override{
    if (numOfSteps <= 0) {
            error("Invalid number of steps: " + std::to_string(numOfSteps));
            return;
        }
    for (int i = 1; i <= numOfSteps; i++){
        simulation.step();
    }
    complete();
}
SimulateStep::const string toString() const override{
    return "SimulateStep: " + std::to_string(numOfSteps) + " steps";
}
SimulateStep* SimulateStep::clone() const override{return new SimulateStep(*this);}



//Constructor
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):settlementName(settlementName), selectionPolicy(selectionPolicy){}
void AddPlan::act(Simulation &simulation) override{
    Settlement* settlement = simulation.getSettlement(settlementName);     
    if (settlement == 0) {//settlement not found           
        error("Settlement " + settlementName + " not found.");
        return;
        }
    SelectionPolicy* selectionPolicy = SelectionPolicy::createSelectionPolicy(selectionPolicyType);
    if (selectionPolicy == 0) {//selection policy not found 
        error("Invalid selection policy: " + selectionPolicyType);
        return;
    }
    simulation.addPlan(settlement, selectionPolicy);
    complete();
}
const string AddPlan::toString() const override{
            return "AddPlan: Settlement Name = " + settlementName + ", Selection Policy = " + selectionPolicy;
        }
AddPlan* AddPlan::clone() const override{return new AddPlan(*this);}






//Constructor
AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):settlementName(settlementName), settlementType(settlementType){} 
void AddSettlement::act(Simulation &simulation) override {
    Settlement* newSettlement = new Settlement(settlementName, SettlementType (settlementType));
    if(!simulation.addSettlement(newSettlement)){
        error("Settlement: " + settlementName +"already exists");
        return;
    }  
    complete();
}
AddSettlement* AddSettlement::clone() const override{return new AddSettlement(*this);}
const string AddSettlement::toString() const override{
    return "AddSettlement: Settlement Name = " + settlementName + ", Settlement Type = " + settlementTypeToString();
}





//Constructor
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
        facilityName(facilityName), facilityCategory(facilityCategory), price(price),lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore){}
void AddFacility::act(Simulation &simulation) override {
    FacilityType& newFacility = FacilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    if(!simulation.addFacility(newFacility)){
        error("Facility: " + facilityName + "already exists");
        return;
    }
    complete();
}
AddFacility* AddFacility::clone() const override{return new AddFacility(*this);}
const string AddFacility::toString() const override{
    return "AddFacility: Facility Name = " + facilityName + 
           ", Category = " + std::to_string(static_cast<int>(facilityCategory)) + 
           ", Price = " + std::to_string(price) + 
           ", LifeQualityImpact = " + std::to_string(lifeQualityScore) + 
           ", EconomyImpact = " + std::to_string(economyScore) + 
           ", EnvironmentImpact = " + std::to_string(environmentScore);
}



//Constructor
PrintPlanStatus::PrintPlanStatus(int planId):planId(planId){}
void PrintPlanStatus::act(Simulation &simulation) override {
    Plan* plan = simulation.getPlan(planId);  
    if (plan == 0) {// checks if the plan exists
        error("Plan: " + planId + "doesn't exist");
        return; 
    }
    cout << plan->toString() << endl;
    complete();
}
PrintPlanStatus* PrintPlanStatus::clone() const override{return new PrintPlanStatus(*this);}
const string PrintPlanStatus::toString() const override{
    return "PrintPlanStatus: PlanID = " + std::to_string(planId);
}




//Constructor

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):planId(planId), newPolicy(newPolicy){}
void ChangePlanPolicy::act(Simulation &simulation) override {
    Plan* plan = simulation.getPlan(planId);
    if (plan == 0) {
        error("Plan: " + planId + "doesn't exist");
        return;
    }
    this->previousPolicy = plan->getSelectionPolicy();
    if (previousPolicy == newPolicy) {
        error("Cannot change selection policy");
        return;
    }
    plan->setSelectionPolicy(newPolicy);//לתקן!!! זה לא צריך לקבל מחרוזת
    complete();
}
ChangePlanPolicy* ChangePlanPolicy::clone() const override{return new ChangePlanPolicy(*this);}
const string ChangePlanPolicy::toString() const override {
    return "ChangePlanPolicy: PlanID = " + std::to_string(planId) + 
           ", Previous Policy = " + previousPolicy + 
           ", New Policy = " + newPolicy;
}





class PrintActionsLog : public BaseAction {
    public:
        PrintActionsLog();
        void act(Simulation &simulation) override;
        PrintActionsLog *clone() const override;
        const string toString() const override;
    private:
};

class Close : public BaseAction {
    public:
        Close();
        void act(Simulation &simulation) override;
        Close *clone() const override;
        const string toString() const override;
    private:
};

class BackupSimulation : public BaseAction {
    public:
        BackupSimulation();
        void act(Simulation &simulation) override;
        BackupSimulation *clone() const override;
        const string toString() const override;
    private:
};


class RestoreSimulation : public BaseAction {
    public:
        RestoreSimulation();
        void act(Simulation &simulation) override;
        RestoreSimulation *clone() const override;
        const string toString() const override;
    private:
};