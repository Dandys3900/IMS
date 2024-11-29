#ifndef CRYPTO_MINER_H
#define CRYPTO_MINER_H

#include "includes.h"

class Coin;
class Exchange;

class CryptoMiner : public Process {
    private:
        CoinsStats coins_mined;
        CoinsStats profits; // Profit for each type of mined coins
        double mining_rate;
        double hardware_performance; // Efficiency of hardware used by miner to mine
        vector<Coin*> coins;
        const string mining_strategy; // Each day select which coin to mine by this strategy

    public:
        CryptoMiner(double initial_rate, double hardware_performance, vector<Coin*> coins, const string mining_strategy);
        ~CryptoMiner();

        void Behavior() override;
        void SetMiningPerformance(double new_value);
        CoinsStats GetTotalMinedCoins();
        void PrintStats();
    
    protected:
        Coin* SelectCoinToMine();
        Coin* SelectCoinToMineRandomChoice();
        Coin* SelectCoinToMineBestChoice();
};

#endif // CRYPTO_MINER_H
