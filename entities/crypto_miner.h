#ifndef CRYPTO_MINER_H
#define CRYPTO_MINER_H

#include "includes.h"

class Coin;

class CryptoMiner : public Process {
    private:
        CoinsStats coins_mined;
        CoinsStats profits; // Profit for each type of mined coin
        double mining_rate;
        double initial_effeciency;
        unordered_set<Coin*> coins;

    public:
        CryptoMiner(double initial_rate, double initial_effeciency, unordered_set<Coin*> coins);
        ~CryptoMiner();

        void Behavior() override;
        void SetMiningEfficiency(double new_value);
        CoinsStats GetTotalMinedCoins();
        void printStats();
};

#endif // CRYPTO_MINER_H
