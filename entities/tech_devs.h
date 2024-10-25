#ifndef TECH_DEVELOPER_H
#define TECH_DEVELOPER_H

#include "crypto_miner.h"
#include <simlib.h>

class TechDeveloper : public Process {
    private:
        // Helps miners mine more coins
        double efficiency_boost;
        CryptoMiner** miners;

    public:
        TechDeveloper(double efficiency_boost, CryptoMiner** miners);
        ~TechDeveloper();

        void Behavior() override;
};

#endif // TECH_DEVELOPER_H
