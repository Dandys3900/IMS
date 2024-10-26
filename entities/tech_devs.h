#ifndef TECH_DEVELOPER_H
#define TECH_DEVELOPER_H

#include "includes.h"
#include "crypto_miner.h"

class TechDeveloper : public Process {
    private:
        // Helps miners mine more coins
        double efficiency_boost;
        unordered_set<CryptoMiner*> miners;

    public:
        TechDeveloper(double efficiency_boost, unordered_set<CryptoMiner*> miners);
        ~TechDeveloper();

        void Behavior() override;
};

#endif // TECH_DEVELOPER_H
