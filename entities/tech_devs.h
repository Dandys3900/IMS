#ifndef TECH_DEVELOPER_H
#define TECH_DEVELOPER_H

#include "includes.h"

class CryptoMiner;

class TechDeveloper : public Process {
    private:
        // Helps miners mine more coins
        double performance_boost;
        vector<CryptoMiner*> miners;

    public:
        TechDeveloper(double performance_boost, vector<CryptoMiner*> miners);
        ~TechDeveloper();

        void Behavior() override;
};

#endif // TECH_DEVELOPER_H
