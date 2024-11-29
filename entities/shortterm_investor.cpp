#include "crypto_coin.h"
#include "crypto_exchange.h"
#include "shortterm_investor.h"

ShortTermInvestor::ShortTermInvestor(CoinsStats initial_balance, CoinsThresholds thresholds, vector<Coin*> coins)
    : Investor(initial_balance, thresholds, coins)
{
}

ShortTermInvestor::~ShortTermInvestor() {

}

void ShortTermInvestor::Behavior() {
    while (true) {
        for (Coin* coin : this->coins) {
            if (coin->GetCurrentPrice() < this->thresholds.at(coin->GetCoinName()).first) {
                this->SellCoins(coin);
            } else if (coin->GetCurrentPrice() > this->thresholds.at(coin->GetCoinName()).second) {
                this->BuyCoins(coin);
            }
        }

        Wait(EVERY_12H);
    }
}

void ShortTermInvestor::BuyCoins(Coin* coin) {
    Exchange* exchange = Exchange::SelectRandomExchangeFor(coin);
    if (coin == nullptr) {
        return;
    }
    double coins_to_buy = Normal((126 / coin->GetCurrentPrice()), 10);;
    coins_to_buy += coins_to_buy * this->GetInvestorSentiment();
    double coins_bought = exchange->ExecuteTransaction(coins_to_buy, this, coin, TransactionType::BUY);
    this->balance.at(coin->GetCoinName()) += coins_bought;
}

void ShortTermInvestor::SellCoins(Coin* coin) {
    Exchange* exchange = Exchange::SelectBestExchangeFor(coin);
    if (coin == nullptr) {
        return;
    }
    // Sell 75% of coins, but at least one whole coin
    double coins_to_sell = this->balance.at(coin->GetCoinName()) > 1.0 ? this->balance.at(coin->GetCoinName()) * 0.75 : 1.0;
    coins_to_sell -= coins_to_sell * this->GetInvestorSentiment();
    double coins_sold = exchange->ExecuteTransaction(coins_to_sell, this, coin, TransactionType::SELL);
    this->balance.at(coin->GetCoinName()) -= coins_sold;
}
