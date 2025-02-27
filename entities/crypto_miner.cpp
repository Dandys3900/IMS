#include "crypto_coin.h"
#include "crypto_exchange.h"
#include "crypto_miner.h"

CryptoMiner::CryptoMiner(double initial_rate, double hardware_performance, vector<Coin*> coins, const string mining_strategy)
    : coins_mined(),
      profits(),
      mining_rate(initial_rate),
      hardware_performance(hardware_performance),
      coins(coins),
      mining_strategy(mining_strategy)
{
    // Init Coinstats
    for (auto coin : this->coins) {
        this->coins_mined.insert({coin->GetCoinName(), 0.0});
        this->profits.insert({coin->GetCoinName(), 0.0});
    }
}

CryptoMiner::~CryptoMiner() {
    this->PrintStats();
}

void CryptoMiner::Behavior() {
    while (true) {
        Wait(EVERY_12H);

        Coin* coin_to_mine = this->SelectCoinToMine();
        if (coin_to_mine == nullptr) {
            continue;
        }

        double coins_mined_per_hour = this->mining_rate * coin_to_mine->GetMiningEfficiency() * this->hardware_performance;
        double mined_amount = coin_to_mine->MineCoins(12 * coins_mined_per_hour);

        // Selected coin is drained for mining, remove it from vector
        if (mined_amount == 0.0) {
            auto element = find(this->coins.begin(), this->coins.end(), coin_to_mine);
            if (element != this->coins.end())
                this->coins.erase(element);
        }

        Exchange* exchange = Exchange::SelectBestExchangeFor(coin_to_mine);
        if (exchange == nullptr) {
            continue;
        }

        Seize(*exchange);
        double profit = exchange->SellCoins(coin_to_mine, mined_amount);
        this->coins_mined.at(coin_to_mine->GetCoinName()) += mined_amount;
        this->profits.at(coin_to_mine->GetCoinName()) += profit;
        Release(*exchange);
    }
}

void CryptoMiner::SetMiningPerformance(double new_value) {
    this->hardware_performance += new_value;
}

void CryptoMiner::PrintStats() {
    cout << "-------------------------"                      << endl;
    cout << "Miner stats:"                                   << endl;
    cout << " -> Current mining rate: " << this->mining_rate << endl;
    cout << " -> Mined coins:"                               << endl;
    for (auto coin : this->coins_mined)
        cout << "Name: " << coin.first << " amount: " << coin.second << endl;
    cout << " -> Profits from coins:" << endl;
    for (auto coin : this->profits)
        cout << "Name: " << coin.first << " profit: " << coin.second << endl;
    cout << "-------------------------" << endl;
}


Coin* CryptoMiner::SelectCoinToMine() {
    if (this->mining_strategy == "random_choice") {
        return SelectCoinToMineRandomChoice();
    }
    if (this->mining_strategy == "best_choice") {
        return SelectCoinToMineBestChoice();
    }
    return nullptr;
}


Coin* CryptoMiner::SelectCoinToMineRandomChoice() {
    if (this->coins.empty()) {
        return nullptr;
    }
    return this->coins.at((std::size_t)Uniform(0, this->coins.size()));
}


Coin* CryptoMiner::SelectCoinToMineBestChoice() {
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
