#include "crypto_investor.h"
#include "crypto_exchange.h"
#include "crypto_coin.h"

Coin::Coin(const string coin_name, double initial_price, double mining_efficiency, double total_supply, double circulating_supply)
    : coin_name(coin_name),
      init_price(initial_price),
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
    this->PrintStats();
}

void Coin::Behavior() {
    while(true) {
        // Every hour, update coin's price
        this->UpdatePrice();

        Wait(EVERY_DAY);
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
    for (auto exchange : this->exchanges) {
        avg_exch_demand += exchange->GetInterestRate(this->coin_name);
    }
    cout << avg_exch_demand << endl;
    // Avoid zero division
    if (!this->exchanges.empty())
        avg_exch_demand = (avg_exch_demand / (double)this->exchanges.size());

    cout << "Coin demand: " << demand << endl;
    cout << "Avg dex demand: " << avg_exch_demand << endl;

    if (demand == 0.0 || avg_exch_demand == 0.0)
        demand = -0.01;
    else // Create total average demand
        demand += avg_exch_demand; //((demand + avg_exch_demand) / 2);

    // Calculate average sentiment among traders
    double avg_sentiment = 0.0;
    for (auto trader : this->traders)
        avg_sentiment += trader->GetInvestorSentiment();
    // Avoid zero division
    if (!this->traders.empty())
        avg_sentiment = (avg_sentiment / this->traders.size());

    double current_time = ceil((Time + 1) / 24.0);
    this->price += (
        pow((current_time / 693), 5.526) * pow(10, (
            pow(0.9998, current_time) * (2 * pow(
            abs(sin(2.983 * sqrt(sqrt(current_time)) - 0.57)) - 1, 2) - 1) * avg_sentiment)
        ) * demand);

    // Avoid negative price
    if (this->price < 0.0)
        this->price = 0.0;

    /*
        // Update price
        this->price += ((demand * this->mining_efficiency * avg_sentiment) / this->total_supply);
    */

    //double current_time = Time + 1;
    //this->price = (this->price * pow(10, pow(0.7, current_time) * sin(2 * M_PI * current_time - 0.4) * demand * avg_sentiment));
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

void Coin::StorePriceHistory() {
    ofstream price_file("price_vals", ios::app);

    if (price_file.is_open()) {
        price_file << "Price history of " << this->coin_name << endl;
        price_file << "-----------------------------------------------" << endl;

        for (auto price : this->price_history)
            price_file << price << ", ";

        price_file << endl << "-----------------------------------------------" << endl;
        price_file.close();
    }
}

void Coin::PrintStats() {
    cout << "-------------------------"           << endl;
    cout << "Coin stats:"                         << endl;
    cout << " -> Name: "                          << this->coin_name << endl;
    cout << " -> Init price: "                    << this->init_price << endl;
    cout << " -> Current price: "                 << this->price << endl;
    cout << " -> Mining efficiency: "             << (this->mining_efficiency * 100) << "%" << endl;
    cout << " -> Count of traders: "               << this->traders.size() << endl;
    cout << " -> Total supply of coins: "         << this->total_supply << endl;
    cout << " -> Coins available for mining: "    << this->available_coins << endl;
    cout << " -> Coins in market (circulating): " << this->circulating_supply << endl;
    cout << "-------------------------"           << endl;

    // Store price history into file
    this->StorePriceHistory();
}
