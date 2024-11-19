#include "crypto_coin.h"
#include "longterm_investor.h"

LongTermInvestor::LongTermInvestor(CoinsStats initial_balance, CoinsThresholds thresholds, unordered_set<Coin*> coins)
    : Investor(initial_balance, thresholds, coins)
{
}

LongTermInvestor::~LongTermInvestor() {

}

void LongTermInvestor::Behavior() {
    // Randomly buys new coins from exchange
    // Amount of new coins is affected by exchange fees
    // For buy and sell behaviour use given values in CoinsThresholds thresholds
}

void LongTermInvestor::BuyCoins(double amount, Coin* coin) {
    // Buy coins from randomly selected exchange
}

void LongTermInvestor::SellCoins(double amount, Coin* coin) {
    // By his intern logic, perform selling of coins
}

void LongTermInvestor::ExchangeClosedReaction() {
    // React to exchange being closed and funds his funds seized, lower amount of coins to buy next time
}
