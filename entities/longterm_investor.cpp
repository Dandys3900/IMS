#include "crypto_coin.h"
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
}

void LongTermInvestor::BuyCoins(double amount, Coin* coin) {
    // Buy coins from randomly selected exchange
}

void LongTermInvestor::SellCoins(double amount, Coin* coin) {
    // By his intern logic, perform selling of coins
}
