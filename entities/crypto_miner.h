#ifndef CRYPTO_MINER_H
#define CRYPTO_MINER_H

#include "crypto_coin.h"
#include <simlib.h>

class CryptoMiner : public Process {
    private:
        double coins_mined;
        double mining_rate;
        double initial_effeciency;
        Coin* coin;

    public:
        CryptoMiner(double initial_rate, double initial_effeciency, Coin* coin);
        ~CryptoMiner();

        void Behavior() override;
        void SetMiningEfficiency(double new_value);
        double GetTotalMinedCoins();
};

#endif // CRYPTO_MINER_H
