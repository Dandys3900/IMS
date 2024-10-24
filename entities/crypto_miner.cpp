#include "crypto_miner.h"

CryptoMiner::CryptoMiner(double initial_rate, double initial_costs, Coin* coin)
    : coins_mined(0.0),
      mining_rate(initial_rate),
      mining_costs(initial_costs),
      coin(coin)
{
}

CryptoMiner::~CryptoMiner() {

}

void CryptoMiner::Behavior() {
    // Mine coins by mining_rate for mining_costs per coin
    // When mining_costs are low compared to coin price, higher mining and vice versa
    // When new coins are mined, update coin:
        //coin->IncreaseSupply(/*mined amount*/);
}

void CryptoMiner::SetMiningCosts(double new_value) {
    this->mining_costs = new_value;
}

double CryptoMiner::GetTotalMinedCoins() {
    return this->coins_mined;
}
