#include "crypto_exchange.h"

Exchange::Exchange(double fee, double init_coins, Investor** customers, Coin* coin)
    : Facility(),
      transaction_fee(fee),
      initial_coins(init_coins),
      sold_coins(0.0),
      stacked_coins(init_coins),
      customers(customers),
      coin(coin)
{
}

Exchange::~Exchange() {

}

void Exchange::ExecuteTransaction(double amount, Investor* buyer, TransactionType type) {
    // Transfer amount of coins to buyer with current fees
    if (type == BUY)
        coin->IncreaseSupply(amount);
    else // type == SELL
        coin->DecreaseSupply(amount);
}

void Exchange::ClosingExchange() {
    // Reaction to when government closes this exchange, send all current customers info
    coin->DecreaseSupply(this->stacked_coins);
}

double Exchange::getInterestRate() {
    // Calculate current value of interest in coins:
    // interest = (stacked_coins / initial_coins)
}
