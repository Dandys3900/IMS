#ifndef CRYPTO_MINER_H
#define CRYPTO_MINER_H

#include "includes.h"

class Coin;

class CryptoMiner : public Process {
    private:
        CoinsStats coins_mined;
        CoinsStats profits; // Profit for each type of mined coins
        double mining_rate;
        double hardware_efficiency; // Efficiency of hardware used by miner to mine
        unordered_set<Coin*> coins;
        const string mining_strategy; // Each day select which coin to mine by this strategy

    public:
        CryptoMiner(double initial_rate, double hardware_efficiency, unordered_set<Coin*> coins, const string mining_strategy);
        ~CryptoMiner();

        void Behavior() override;
        void SetMiningEfficiency(double new_value);
        CoinsStats GetTotalMinedCoins();
        void PrintStats();
};

#endif // CRYPTO_MINER_H
