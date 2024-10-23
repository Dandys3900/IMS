#ifndef CRYPTO_MINER_H
#define CRYPTO_MINER_H

#include "includes.h"

class CryptoMiner : public Process {
    private:
        double coins_mined;
        double mining_rate;
        double mining_costs;

    public:
        CryptoMiner(double initial_rate, double initial_costs);
        ~CryptoMiner();

        void Behavior() override;
        void SetMiningCosts(double new_value);
        const double GetTotalMinedCoins();
};

#endif // CRYPTO_MINER_H
