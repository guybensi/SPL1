#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath);//new method******
        Simulation(const Simulation &other);// Copy Constructor
        Simulation& operator=(const Simulation &other);// Copy Assignment Operator
        void start();// ------------
        void addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy);//********updated function
        void addAction(BaseAction *action);// ------------
        bool addSettlement(Settlement *settlement);//********updated function
        bool addFacility(FacilityType facility);//********updated function
        bool isFacilityExists(const string &facilityName);//our method
        bool isSettlementExists(const string &settlementName);
        Settlement *getSettlement(const string &settlementName);
        Plan &getPlan(const int planID);
        void step();//new method******
        void close();//new method******
        void open();//new method******
        ~Simulation();// Destructor

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;

};