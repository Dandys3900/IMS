#include "longterm_investor.h"

LongTermInvestor::LongTermInvestor(double initial_balance)
    : Investor(balance)
{
}

LongTermInvestor::~LongTermInvestor() {

}

void LongTermInvestor::Behavior() override {
    // Randomly buys new coins from exchange
    // Amount of new coins is affected by exchange fees
}

void LongTermInvestor::BuyCoins(double amount) override {
    // Buy coins from randomly selected exchange
}

void LongTermInvestor::SellCoins(double amount) override {
    // By his intern logic, perform selling of coins
}

void LongTermInvestor::ExchangeClosedReaction() override {
    // React to exchange being closed and funds his funds seized, lower amount of coins to buy next time
}
