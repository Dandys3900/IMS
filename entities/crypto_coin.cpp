#include "base_investor.h"
#include "crypto_exchange.h"
#include "crypto_coin.h"

Coin::Coin(const string coin_name, double initial_price, double mining_efficiency, double total_supply, double circulating_supply)
    : coin_name(coin_name),
      price(initial_price),
      mining_efficiency(mining_efficiency),
      total_supply(total_supply),
      circulating_supply(circulating_supply),
      available_coins(total_supply - circulating_supply),
      traders(),
      price_history()
{
}

Coin::~Coin() {

}

void Coin::Behavior() {
    while(true) {
        // Every hour, update coin's price
        this->UpdatePrice();

        Wait(EVERY_HOUR);
    }
}

void Coin::IncreaseSupply(double amount) {
    this->circulating_supply += amount;
}

void Coin::DecreaseSupply(double amount) {
    this->circulating_supply -= amount;
}

void Coin::ChangePrice(double factor) {
    // Method called by Elon tweet to suddenly change coin price
    this->price += (this->price * factor);

    if (factor > 0.0) {
        // Distribute this positive news to coin's traders
        for (auto trader : this->traders)
            trader->PositiveNewsReaction();
    }
    else {
        // Distribute this negative news to coin's traders
        for (auto trader : this->traders)
            trader->NegativeNewsReaction();
    }
}

void Coin::UpdatePrice() {
    // Archive coin's price before update
    this->price_history.push_back(this->price);

    // Internal logic to calculate new price of coin
    // Demand by market
    double demand = (this->circulating_supply / this->total_supply);

    // Calculate average demand from each exchange trading this coin
    double avg_exch_demand = 0.0;
    for (auto exchange : this->exchanges)
        avg_exch_demand += exchange->GetInterestRate(this->coin_name);
    avg_exch_demand = (avg_exch_demand / this->exchanges.size());

    // Create total average demand
    demand = ((demand + avg_exch_demand) / 2);

    // Calculate average sentiment among traders
    double avg_sentiment = 0.0;
    for (auto trader : this->traders)
        avg_sentiment += trader->GetInvestorSentiment();
    avg_sentiment = (avg_sentiment / this->traders.size());

    // Update price
    this->price *= (demand + avg_sentiment);
}

double Coin::MineCoins(double amount) {
    // Given amount is available
    if (amount <= this->available_coins) {
        this->available_coins -= amount;
        this->IncreaseSupply(amount);
        return amount;
    }

    // We don't have enough, return what we have
    double current_amount = this->available_coins;
    this->available_coins = 0.0;
    this->IncreaseSupply(current_amount);

    return current_amount;
}

const string Coin::GetCoinName() {
    return this->coin_name;
}

double Coin::GetCurrentPrice() {
    return this->price;
}

double Coin::GetMiningEfficiency() {
    return this->mining_efficiency;
}

vector<Exchange*> Coin::GetExchanges() {
    return this->exchanges;
}

void Coin::AddExchange(Exchange* exchange) {
    // Add new exchange trading this coin
    this->exchanges.push_back(exchange);
}

void Coin::AddTrader(Investor* trader) {
    // Add new trader trading this coin
    this->traders.push_back(trader);
}

vector<Investor*> Coin::GetTraders() {
    return this->traders;
}

vector<double> Coin::GetPriceHistory() {
    return this->price_history;
}

void Coin::PrintStats() {
    cout << "-------------------------"           << endl;
    cout << "Coin stats:"                         << endl;
    cout << " -> Name: "                          << this->GetCoinName() << endl;
    cout << " -> Current price: "                 << this->GetCurrentPrice() << endl;
    cout << " -> Mining efficiency: "             << this->GetMiningEfficiency() << endl;
    cout << " -> Count of traders:"               << this->GetTraders().size() << endl;
    cout << " -> Total supply of coins: "         << this->total_supply << endl;
    cout << " -> Coins available for mining: "    << this->available_coins << endl;
    cout << " -> Coins in market (circulating): " << this->circulating_supply << endl;
    cout << "-------------------------"           << endl;
}
