#include "crypto_exchange.h"

Exchange::Exchange(double fee, double init_coins, double gov_taxes, unordered_set<Investor*> customers, Coin* coin)
    : Facility(),
      transaction_fee(fee),
      initial_coins(init_coins),
      sold_coins(0.0),
      stacked_coins(init_coins),
      gov_taxes(gov_taxes),
      customers(customers),
      coin(coin)
{
}

Exchange::~Exchange() {

}

double Exchange::ExecuteTransaction(double amount, Investor* buyer, TransactionType type) {
    // Transfer amount of coins to buyer with current fees
    if (type == BUY)
        coin->IncreaseSupply(amount);
    else // type == SELL
        coin->DecreaseSupply(amount);
    // Apply government taxes and idividual exchange fee
    return amount * (1.0 - this->gov_taxes) * (1.0 - this->transaction_fee);
}

void Exchange::ClosingExchange() {
    // Reaction to when government closes this exchange, send all current customers info
    coin->DecreaseSupply(this->stacked_coins);

    for(auto customer : this->customers)
        customer->ExchangeClosedReaction();
}

double Exchange::getInterestRate() {
    // Calculate current value of interest in coins:
    // interest = (stacked_coins / initial_coins)
}

void Exchange::UpdateGovTaxes(double new_value) {
    this->gov_taxes = new_value;
}
