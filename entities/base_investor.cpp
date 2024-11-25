#include "base_investor.h"
#include "crypto_coin.h"

Investor::Investor(CoinsStats initial_balance, CoinsThresholds thresholds, vector<Coin*> coins)
    : balance(initial_balance),
      thresholds(thresholds),
      coins(coins),
      sentiment(0.0)
{
    // Link investor with coins
    for (auto coin : this->coins)
        coin->AddTrader(this);
}

void Investor::PositiveNewsReaction() {
    // Results in higher investor sentiment value affected by good news
    // Randomly select how affected this investor is
    this->sentiment = Uniform(0.0, 1.0);
}

void Investor::NegativeNewsReaction() {
    // Results in lowering investor sentiment value affected by bad news
    // Randomly select how affected this investor is
    this->sentiment = Uniform(-1.0, 0.0);
}

double Investor::GetInvestorSentiment() {
    return this->sentiment;
}

void Investor::PrintStats() {
    cout << "-------------------------" << endl;
    cout << "Investor stats:"           << endl;
    cout << " -> Traided coins: "       << endl;
    for (auto coin : this->coins) {
        string coinname = coin->GetCoinName();
        cout << "Name: " << coinname << " final balance: " << this->balance.at(coinname) << endl;
        cout << "Sell threshold: " << this->thresholds.at(coinname).first << endl;
        cout << "Buy threshold: " << this->thresholds.at(coinname).second << endl;
    }
    cout << "-------------------------" << endl;
}
