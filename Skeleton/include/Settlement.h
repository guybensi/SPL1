#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Facility;

enum class SettlementType {
    VILLAGE,
    CITY,
    METROPOLIS,
};

class Settlement {
    public:
        Settlement(const string &name, SettlementType type);
        const string &getName() const;
        SettlementType getType() const;
        const string settlementTypeToString() const//new method****
        const string toString() const;//updated method****
        int getLimit();//our method

        private:
            const string name;
            SettlementType type;
            int limit;
};