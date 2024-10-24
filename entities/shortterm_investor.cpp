#include "longterm_investor.h"

ShortTermInvestor::ShortTermInvestor(double initial_balance, Coin* coin)
    : Investor(initial_balance, coin)
{
}

ShortTermInvestor::~ShortTermInvestor() {

}

void ShortTermInvestor::Behavior() {
    // Randomly buys random amount of new coins from exchange
    // Amount of new coins is affected by exchange fees
}

void ShortTermInvestor::BuyCoins(double amount) {
    // Buy coins from randomly selected exchange
    // When price is rising buy many new coins, no strategy
}

void ShortTermInvestor::SellCoins(double amount) {
    // By his intern logic, perform selling of coins
    // Even for tiny price drop, sell most of them in fear
}

void ShortTermInvestor::ExchangeClosedReaction() {
    // React to exchange being closed and funds his funds seized, lower amount of coins to buy next time
}
