#include "crypto_miner.h"

CryptoMiner::CryptoMiner(double initial_rate, double initial_effeciency, Coin* coin)
    : coins_mined(0.0),
      mining_rate(initial_rate),
      initial_effeciency(initial_effeciency),
      coin(coin)
{
}

CryptoMiner::~CryptoMiner() {

}

void CryptoMiner::Behavior() {
    // Mine coins by mining_rate for mining_costs per coin
    // When mining_costs are low compared to coin price, higher mining and vice versa
    // double amount = /*CALCULATE*/ 100;
    // double mined_amount = coin->MineCoins(amount);
    // Lower mining rate
    // if (mined_amount != amount) {
       // this->mining_rate *= 0.8;
    //}
    // When new coins are mined, update coin:
        //coin->IncreaseSupply(/*mined amount*/);
}

void CryptoMiner::SetMiningEfficiency(double new_value) {
    this->initial_effeciency = new_value;
}

double CryptoMiner::GetTotalMinedCoins() {
    return this->coins_mined;
}
