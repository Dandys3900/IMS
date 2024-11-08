#include "crypto_coin.h"
#include "base_investor.h"
#include "crypto_exchange.h"

Exchange::Exchange(double fee, CoinsStats init_coins, double gov_taxes, unordered_set<Investor*> customers, unordered_set<Coin*> coins)
    : Facility(),
      transaction_fee(fee),
      initial_coins(init_coins),
      sold_coins(0.0),
      stacked_coins(init_coins),
      gov_taxes(gov_taxes),
      customers(customers),
      coins(coins),
      closed_by_gov(false)
{
    // Iterate over all given coins and add this exchange to their list
    for (auto coin : this->coins)
        coin->addTradingExchange(this);
}

Exchange::~Exchange() {

}

double Exchange::ExecuteTransaction(double amount, Investor* buyer, Coin* coin, TransactionType type) {
    // Get current amount of requested coin
    double& coin_amount = this->stacked_coins.at(coin->getCoinName());

    // Transfer amount of coins to buyer with current fees
    if (type == BUY) {
        // Check if exchange has enough of coins, otherwise send 0.0 to try another exchange
        if (coin_amount < amount)
            return 0.0;

        coin->IncreaseSupply(amount);
        // Update exchange current amount of this coin
        coin_amount -= amount;
    }
    else { // type == SELL
        coin->DecreaseSupply(amount);
        // Update exchange current amount of this coin
        coin_amount += amount;
    }
    // Apply government taxes and individual exchange fee
    return amount * (1.0 - this->gov_taxes) * (1.0 - this->transaction_fee);
}

void Exchange::ClosingExchange() {
    this->closed_by_gov = true;
    // For all traded coins, update their supplies
    for (auto coin : this->coins)
        coin->DecreaseSupply(this->stacked_coins.at(coin->getCoinName()));

    // Reaction to when government closes this exchange, send all current customers info
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

void Exchange::printStats() {
    cout << "-------------------------"                           << endl;
    cout << "Exchange stats:"                                     << endl;
    cout << " -> Taxes: " << this->gov_taxes                      << endl;
    cout << " -> Number of customers: " << this->customers.size() << endl;
    cout << " -> Traded coins: "                                  << endl;
    for (auto coin : this->coins) {
        string coinname = coin->getCoinName();
        cout << "Name: " << coinname << "amount: " << this->stacked_coins.at(coinname) << endl;
    }
    cout << " -> Closed by government: " << this->closed_by_gov << endl;
    cout << "-------------------------"                         << endl;
}
