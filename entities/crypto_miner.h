#ifndef CRYPTO_MINER_H
#define CRYPTO_MINER_H

#include "includes.h"

class CryptoMiner : public Process {
    private:
        double coins_mined;
        double mining_rate;
        double mining_costs;
        Coin* coin;

    public:
        CryptoMiner(double initial_rate, double initial_costs, Coin* coin);
        ~CryptoMiner();

        void Behavior() override;
        void SetMiningCosts(double new_value);
        double GetTotalMinedCoins();
};

#endif // CRYPTO_MINER_H
