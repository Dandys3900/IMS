#include "crypto_coin.h"
#include "crypto_miner.h"

CryptoMiner::CryptoMiner(double initial_rate, double hardware_performance, vector<Coin*> coins, const string mining_strategy)
    : coins_mined(),
      profits(),
      mining_rate(initial_rate),
      hardware_performance(hardware_performance),
      coins(coins),
      mining_strategy(mining_strategy)
{
}

CryptoMiner::~CryptoMiner() {

}

void CryptoMiner::Behavior() {
    // Select coin to mine by given strategy:
    // -> 1. random_choice - from coins set, randomly select one
    // -> 2. best_choice - choice by combination of coin with highest current price and its efficiency of mining (use GetMiningEfficiency() method)
    // -> 3. first_choice - select the first coin in set (DESIGNED FOR CASE WHERE MINER'S COINS LIST HAS ONLY ONE COIN SET)
    // When selling it to exchange, choose exchange with lowest fees, if returns 0.0 it means to try another one
    // Mine coins by mining_rate for mining_costs per coin
    // When mining_costs are low compared to coin price, higher mining and vice versa
    // double amount = /*CALCULATE*/ 100; (INCLUDE hardware_performance INTO CALCULATIONS)
    // double mined_amount = coin->MineCoins(amount);
    // Lower mining rate
    // if (mined_amount != amount) {
       // this->mining_rate *= 0.8;
    //}
    // When new coins are mined, update coin:
        //coin->IncreaseSupply(/*mined amount*/);
}

void CryptoMiner::SetMiningPerformance(double new_value) {
    this->hardware_performance += new_value;
}

CoinsStats CryptoMiner::GetTotalMinedCoins() {
    return this->coins_mined;
}

void CryptoMiner::PrintStats() {
    cout << "-------------------------"                      << endl;
    cout << "Miner stats:"                                   << endl;
    cout << " -> Current mining rate: " << this->mining_rate << endl;
    cout << " -> Mined coins:"                               << endl;
    for (auto coin : this->coins) {
        string coinname = coin->GetCoinName();
        cout << "Name: " << coinname << " amount: " << this->GetTotalMinedCoins().at(coinname) << endl;
    }
    cout << " -> Profits from coins:" << endl;
    for (auto coin : this->coins) {
        string coinname = coin->GetCoinName();
        cout << "Name: " << coinname << " profit: " << this->profits.at(coinname) << endl;
    }
    cout << "-------------------------" << endl;
}
