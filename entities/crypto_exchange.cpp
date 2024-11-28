#include "crypto_coin.h"
#include "base_investor.h"
#include "crypto_exchange.h"

Exchange::Exchange(double fee, CoinsStats init_coins, vector<Investor*> customers, vector<Coin*> coins)
    : Facility(),
      transaction_fee(fee),
      initial_coins(init_coins),
      sold_coins(0.0),
      stacked_coins(init_coins),
      gov_taxes(0.0),
      customers(customers),
      coins(coins),
      closed_by_gov(false)
{
    // Register this exchange to all coins it trades
    for (auto coin : this->coins)
        coin->AddExchange(this);
}

Exchange::~Exchange() {

}

double Exchange::ExecuteTransaction(double amount, Investor* buyer, Coin* coin, TransactionType type) {
    if (this->closed_by_gov)
        return 0.0;

    // Get current amount of requested coin
    double& coin_amount = this->stacked_coins.at(coin->GetCoinName());

    // Transfer amount of coins to buyer with current fees
    if (type == BUY) {
        // Check if exchange has enough of coins, otherwise send 0.0 to try another exchange
        if (coin_amount < amount)
            return 0.0;

        coin->IncreaseSupply(amount);
        // Update exchange current amount of this coin
        coin_amount -= amount;

        // Update total amount of sold coins
        this->sold_coins +- amount;
    }
    else { // type == SELL
        coin->DecreaseSupply(amount);
        // Update exchange current amount of this coin
        coin_amount += amount;
    }
    // Apply government taxes and individual exchange fee
    return amount * this->GetTolalFeeFactor();
}

void Exchange::ClosingExchange() {
    this->closed_by_gov = true;
    // For all traded coins, update their supplies
    for (auto coin : this->coins)
        coin->DecreaseSupply(this->stacked_coins.at(coin->GetCoinName()));

    // Reaction to when government closes this exchange, send all current customers info
    for(auto customer : this->customers)
        customer->NegativeNewsReaction();
}

double Exchange::GetInterestRate(const string coin_name) {
    // Calculate current value of interest for given coin
    double stacked_coins = this->stacked_coins.at(coin_name);
    double initial_amount = this->initial_coins.at(coin_name);

    return (stacked_coins / initial_amount);
}

double Exchange::GetTolalFeeFactor() {
    return (1.0 - this->gov_taxes) * (1.0 - this->transaction_fee);
}

void Exchange::UpdateGovTaxes(double new_value) {
    this->gov_taxes = new_value;
}

bool Exchange::IsClosed() {
    return this->closed_by_gov;
}

void Exchange::PrintStats() {
    cout << "-------------------------"                           << endl;
    cout << "Exchange stats:"                                     << endl;
    cout << " -> Taxes: " << this->gov_taxes                      << endl;
    cout << " -> Number of customers: " << this->customers.size() << endl;
    cout << " -> Traded coins: "                                  << endl;
    for (auto coin : this->coins) {
        string coinname = coin->GetCoinName();
        cout << "Name: " << coinname << "amount: " << this->stacked_coins.at(coinname) << endl;
    }
    cout << " -> Closed by government: " << this->closed_by_gov << endl;
    cout << "-------------------------"                         << endl;
}
