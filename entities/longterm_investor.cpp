#include "crypto_coin.h"
#include "crypto_exchange.h"
#include "longterm_investor.h"

LongTermInvestor::LongTermInvestor(CoinsStats initial_balance, CoinsThresholds thresholds, vector<Coin*> coins)
    : Investor(initial_balance, thresholds, coins)
{
}

LongTermInvestor::~LongTermInvestor() {

}

void LongTermInvestor::Behavior() {
    // Randomly buys new coins from exchange
    // Amount of new coins is affected by exchange fees
    // For buy and sell behaviour use given values in CoinsThresholds thresholds
    // Consider his current sentiment (mood)
    while (true) {
        for (Coin* coin : this->coins) {
            if (coin->GetCurrentPrice() < this->thresholds.at(coin->GetCoinName()).first) {
                this->SellCoins(coin);
            } else if (coin->GetCurrentPrice() > this->thresholds.at(coin->GetCoinName()).second) {
                this->BuyCoins(coin);
            }
        }

        Wait(EVERY_WEEK);
    }
}

void LongTermInvestor::BuyCoins(Coin* coin) {
    // Buy coins from randomly selected exchange
    Exchange* exchange = Exchange::SelectRandomExchangeFor(coin);
    if (coin == nullptr) {
        return;
    }
    double coins_to_buy = Normal(50, 10);
    coins_to_buy += coins_to_buy * this->GetInvestorSentiment() * 0.5; // not as affected by his sentiment
    double coins_bought = exchange->ExecuteTransaction(coins_to_buy, this, coin, TransactionType::BUY);
    this->balance.at(coin->GetCoinName()) += coins_bought;
}

void LongTermInvestor::SellCoins(Coin* coin) {
    // By his intern logic, perform selling of coins
    Exchange* exchange = Exchange::SelectBestExchangeFor(coin);
    if (coin == nullptr) {
        return;
    }
    // Sell 75% of coins, but at least one whole coin
    double coins_to_sell = this->balance.at(coin->GetCoinName()) > 1.0 ? this->balance.at(coin->GetCoinName()) * 0.75 : 1.0;
    coins_to_sell -= coins_to_sell * this->GetInvestorSentiment() * 0.25; // not as affected by his sentiment
    double coins_sold = exchange->ExecuteTransaction(coins_to_sell, this, coin, TransactionType::SELL);
    this->balance.at(coin->GetCoinName()) -= coins_sold;
}
