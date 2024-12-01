#include "crypto_coin.h"
#include "crypto_investor.h"
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
      closed_by_gov(false),
      change_volume()
{
    // Register this exchange to all coins it trades
    for (auto coin : this->coins) {
        coin->AddExchange(this);
        this->change_volume.insert({coin->GetCoinName(), 0.0});
    }
}

Exchange::~Exchange() {
    this->PrintStats();
}

// Buy coins from exchange
double Exchange::BuyCoins(Coin* coin, double amount) {
    amount = min(amount, this->stacked_coins.at(coin->GetCoinName()));

    coin->IncreaseSupply(amount);
    // Update volume of coins being circulating
    this->change_volume.at(coin->GetCoinName()) += amount;
    // Update exchange current amount of this coin
    this->stacked_coins.at(coin->GetCoinName()) -= amount;
    // Update total amount of sold coins
    this->sold_coins += amount;
    // Return actual number of bought coins. Apply government taxes and individual exchange fee
    return amount * this->GetTotalFeeFactor();
}

// Sell coins to exchange
double Exchange::SellCoins(Coin* coin, double amount) {
    coin->IncreaseSupply(amount);
    // Update volume of coins being circulating
    this->change_volume.at(coin->GetCoinName()) += amount;
    // Update exchange current amount of this coin
    this->stacked_coins.at(coin->GetCoinName()) += amount;
    // Return money amount from this transaction. Apply government taxes and individual exchange fee
    return amount * coin->GetCurrentPrice() * this->GetTotalFeeFactor();
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
    double stacked_coins = this->change_volume.at(coin_name);
    double initial_amount = this->initial_coins.at(coin_name);

    // Reset volume for given coin
    this->change_volume.at(coin_name) = 0.0;

    return (stacked_coins / initial_amount);
}

double Exchange::GetTotalFeeFactor() {
    return (1.0 - this->gov_taxes) * (1.0 - this->transaction_fee);
}

void Exchange::UpdateGovTaxes(double new_value) {
    this->gov_taxes = new_value;
}

bool Exchange::IsClosed() {
    return this->closed_by_gov;
}

bool Exchange::HasCoins(Coin* coin) {
    return this->stacked_coins.at(coin->GetCoinName()) > 0.0;
}

void Exchange::PrintStats() {
    cout << "-------------------------"                           << endl;
    cout << "Exchange stats:"                                     << endl;
    cout << " -> Taxes: " << (this->gov_taxes * 100) << " %"      << endl;
    cout << " -> Sold coins: " << this->sold_coins                << endl;
    cout << " -> Number of customers: " << this->customers.size() << endl;
    cout << " -> Traded coins: "                                  << endl;
    for (auto coin : this->stacked_coins)
        cout << "Name: " << coin.first << " amount: " << coin.second << endl;
    cout << " -> Closed by government: " << (this->closed_by_gov ? "true" : "false") << endl;
    cout << "-------------------------" << endl;
}

Exchange* Exchange::SelectRandomExchangeFor(Coin* coin) {
    vector<Exchange*> usable_exchanges = {};
    for (Exchange* exchange : coin->GetExchanges()) {
        if (exchange->HasCoins(coin)) {
            usable_exchanges.push_back(exchange);
        }
    }
    if (usable_exchanges.empty()) {
        return nullptr;
    }
    return usable_exchanges.at((size_t)Uniform(0, usable_exchanges.size()));
}

Exchange* Exchange::SelectBestExchangeFor(Coin* coin) {
    Exchange* best_exchange = nullptr;
    double best_exchange_fee_factor = 0.0;
    for (Exchange* exchange : coin->GetExchanges()) {
        if (!exchange->IsClosed() && exchange->HasCoins(coin) && exchange->GetTotalFeeFactor() >= best_exchange_fee_factor) {
            best_exchange = exchange;
            best_exchange_fee_factor = exchange->GetTotalFeeFactor();
        }
    }
    return best_exchange;
}
