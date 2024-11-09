#include "crypto_coin.h"
#include "crypto_miner.h"

CryptoMiner::CryptoMiner(double initial_rate, double initial_effeciency, unordered_set<Coin*> coins)
    : coins_mined(),
      profits(),
      mining_rate(initial_rate),
      initial_effeciency(initial_effeciency),
      coins(coins)
{
}

CryptoMiner::~CryptoMiner() {

}

void CryptoMiner::Behavior() {
    // Select coin to mine by its current price
    // When selling it to exchange, choose exchange with lowest fees, if returns 0.0 it means to try another one
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

CoinsStats CryptoMiner::GetTotalMinedCoins() {
    return this->coins_mined;
}

void CryptoMiner::printStats() {
    cout << "-------------------------"                      << endl;
    cout << "Miner stats:"                                   << endl;
    cout << " -> Current mining rate: " << this->mining_rate << endl;
    cout << " -> Mined coins:"                               << endl;
    for (auto coin : this->coins) {
        string coinname = coin->getCoinName();
        cout << "Name: " << coinname << " amount: " << this->GetTotalMinedCoins().at(coinname) << endl;
    }
    cout << " -> Profits from coins:" << endl;
    for (auto coin : this->coins) {
        string coinname = coin->getCoinName();
        cout << "Name: " << coinname << " profit: " << this->profits.at(coinname) << endl;
    }
    cout << "-------------------------" << endl;
}
