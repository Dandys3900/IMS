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
    Coin* coin_to_mine = this->select_coin_to_mine();
    if (coin_to_mine == nullptr) {
        return;
    }

    double coins_mined_per_hour = this->mining_rate * coin_to_mine->GetMiningEfficiency() * this->hardware_performance;
    double hours_to_mine = ceil(1 / coins_mined_per_hour);
    Wait(hours_to_mine); // Wait the minimal amount of time to mine at least one whole coin 
    double mined_amount = coin_to_mine->MineCoins(hours_to_mine * coins_mined_per_hour);
    // ?????
    // double mined_amount = coin->MineCoins(amount);
    // Lower mining rate
    // if (mined_amount != amount) {
       // this->mining_rate *= 0.8;
    //}

    Exchange* exchange = this->select_best_exchange_for(coin_to_mine);
    if (exchange == nullptr) {
        return;
    }
    double profit = exchange->ExecuteTransaction(mined_amount, nullptr, coin_to_mine, TransactionType::SELL);
    this->coins_mined.at(coin_to_mine->GetCoinName()) += mined_amount;
    this->profits.at(coin_to_mine->GetCoinName()) += profit;
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


Coin* CryptoMiner::select_coin_to_mine() {
    if (this->mining_strategy == "random_choice") {
        return select_coin_to_mine_random_choice();
    }
    if (this->mining_strategy == "best_choice") {
        return select_coin_to_mine_best_choice();
    }
    return nullptr;
}


Coin* CryptoMiner::select_coin_to_mine_random_choice() {
    if (this->coins.empty()) {
        return nullptr;
    }
    return this->coins.at((std::size_t)Uniform(0, this->coins.size()));
}


Coin* CryptoMiner::select_coin_to_mine_best_choice() {
    Coin* best_coin = nullptr;
    double best_coin_utility = 0.0;
    for (Coin* coin : this->coins) {
        double current_coin_utility = coin->GetCurrentPrice() * this->mining_rate * coin->GetMiningEfficiency() * this->hardware_performance;
        if (current_coin_utility >= best_coin_utility) {
            best_coin = coin;
            best_coin_utility = current_coin_utility;
        }
    }
    return best_coin;
}


Exchange* CryptoMiner::select_best_exchange_for(Coin* coin) {
    Exchange* best_exchange = nullptr;
    double best_exchange_fee_factor = 0.0;
    for (Exchange* exchange : coin->GetExchanges()) {
        if (!exchange->IsClosed() && exchange->GetTolalFeeFactor() >= best_exchange_fee_factor) {
            best_exchange = exchange;
            best_exchange_fee_factor = exchange->GetTolalFeeFactor();
        }
    }
    return best_exchange;
}
