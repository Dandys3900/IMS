#include "longterm_investor.h"

LongTermInvestor::LongTermInvestor(double initial_balance, Coin* coin)
    : Investor(initial_balance, coin)
{
}

LongTermInvestor::~LongTermInvestor() {

}

void LongTermInvestor::Behavior() {
    // Randomly buys new coins from exchange
    // Amount of new coins is affected by exchange fees
}

void LongTermInvestor::BuyCoins(double amount) {
    // Buy coins from randomly selected exchange
}

void LongTermInvestor::SellCoins(double amount) {
    // By his intern logic, perform selling of coins
}

void LongTermInvestor::ExchangeClosedReaction() {
    // React to exchange being closed and funds his funds seized, lower amount of coins to buy next time
}
