#include "crypto_coin.h"
#include "shortterm_investor.h"

ShortTermInvestor::ShortTermInvestor(CoinsStats initial_balance, CoinsThresholds thresholds, vector<Coin*> coins)
    : Investor(initial_balance, thresholds, coins)
{
}

ShortTermInvestor::~ShortTermInvestor() {

}

void ShortTermInvestor::Behavior() {
    // Randomly buys random amount of new coins from exchange
    // Amount of new coins is affected by exchange fees
    // For buy and sell behaviour use given values in CoinsThresholds thresholds
    // Consider his current sentiment (mood)
}

void ShortTermInvestor::BuyCoins(double amount, Coin* coin) {
    // Buy coins from randomly selected exchange
    // When price is rising buy many new coins, no strategy
}

void ShortTermInvestor::SellCoins(double amount, Coin* coin) {
    // By his intern logic, perform selling of coins
    // Even for tiny price drop, sell most of them in fear
}
