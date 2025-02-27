#include "crypto_investor.h"
#include "crypto_exchange.h"
#include "crypto_coin.h"

Investor::Investor(InvestorType investor_type, CoinsStats initial_balance, CoinsThresholds thresholds, vector<Coin*> coins)
    : investor_type(investor_type),
      balance(initial_balance),
      thresholds(thresholds),
      coins(coins),
      sentiment(0.0)
{
    // Link investor with coins
    for (auto coin : this->coins)
        coin->AddTrader(this);
}

Investor::~Investor() {
	this->PrintStats();
}

void Investor::Behavior() {
	 while (true) {
        for (Coin* coin : this->coins) {
            if (coin->GetCurrentPrice() > this->thresholds.at(coin->GetCoinName()).first) {
                this->SellCoins(coin);
            } else if (coin->GetCurrentPrice() < this->thresholds.at(coin->GetCoinName()).second && coin->GetCurrentPrice() > 0.0) {
                this->BuyCoins(coin);
            }
        }

        Wait(this->investor_type == InvestorType::SHORT_TERM ? EVERY_12H : EVERY_WEEK);
    }
}

void Investor::BuyCoins(Coin* coin) {
    Exchange* exchange = Exchange::SelectRandomExchangeFor(coin);
    if (exchange == nullptr) {
        return;
    }

	// Buy roughly 84$ worth of coins
    double coins_to_buy = (84 / coin->GetCurrentPrice());
	// Sentiment effect - buy more when sentiment is high and buy less when sentiment is low. Long term investor is not as affected by sentiment when buying
    coins_to_buy += coins_to_buy * this->GetInvestorSentiment() * (this->investor_type == InvestorType::SHORT_TERM ? 1.0 : 0.5);

    // Too low sentiment, don't buy any
    if (coins_to_buy <= 0.0) {
        return;
    }

    Seize(*exchange);
    double coins_bought = exchange->BuyCoins(coin, coins_to_buy);
    this->balance.at(coin->GetCoinName()) += coins_bought;
    Release(*exchange);
}

void Investor::SellCoins(Coin* coin) {
    Exchange* exchange = Exchange::SelectBestExchangeFor(coin);
    if (exchange == nullptr) {
        return;
    }

    // Sell some of the coins
    double coins_to_sell = this->balance.at(coin->GetCoinName()) * (this->investor_type == InvestorType::SHORT_TERM ? 0.75 : 0.5);
	// Sentiment effect - sell more when sentiment is low and sell less when sentiment is high. Long term investor is not as affected by sentiment when selling
    coins_to_sell += coins_to_sell * this->GetInvestorSentiment() * (this->investor_type == InvestorType::SHORT_TERM ? 1.0 : 0.25);

    // Too low sentiment, don't sell any
    if (coins_to_sell <= 0.0 || this->balance.at(coin->GetCoinName()) < coins_to_sell) {
        return;
    }

    Seize(*exchange);
	// Sell the coins
    exchange->SellCoins(coin, coins_to_sell);
    this->balance.at(coin->GetCoinName()) -= coins_to_sell;
    Release(*exchange);
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
    for (auto coin : this->balance) {
        string coinname = coin.first;
        cout << "Name: " << coinname << " final balance: " << coin.second << endl;
        cout << "Sell threshold: " << this->thresholds.at(coinname).first << endl;
        cout << "Buy threshold: " << this->thresholds.at(coinname).second << endl;
    }
    cout << "-------------------------" << endl;
}