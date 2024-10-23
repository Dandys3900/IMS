#include "crypto_miner.h"

CryptoMiner::CryptoMiner(double initial_rate, double initial_costs)
    : coins_mined(0.0),
      mining_rate(initial_rate),
      mining_costs(initial_costs)
{
}

CryptoMiner::~CryptoMiner() {

}

void CryptoMiner::Behavior() override {
    // Mine coins by mining_rate for mining_costs per coin
    // When mining_costs are low compared to coin price, higher mining and vice versa
}

void CryptoMiner::SetMiningCosts(double new_value) {
    this->mining_costs = new_value;
}

const double CryptoMiner::GetTotalMinedCoins() {
    return this->coins_mined;
}
