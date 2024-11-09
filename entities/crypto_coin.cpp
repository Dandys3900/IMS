#include "crypto_exchange.h"
#include "crypto_coin.h"

Coin::Coin(const string coin_name, double initial_price, double total_supply, double circulating_supply)
    : coin_name(coin_name),
      price(initial_price),
      total_supply(total_supply),
      circulating_supply(circulating_supply),
      available_coins(total_supply - circulating_supply),
      trading_exchanges()
{
}

Coin::~Coin() {

}

void Coin::IncreaseSupply(double amount) {
    this->circulating_supply += amount;
}

void Coin::DecreaseSupply(double amount) {
    this->circulating_supply -= amount;
}

void Coin::IncreasePrice(double factor) {
    // Method called by Elon tweet to suddenly change coin price
}

void Coin::DecreasePrice(double factor) {
    // Method called by Elon tweet to suddenly change coin price
}

void Coin::UpdatePrice() {
    // Internal logic to calculate new price of coin
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

const string Coin::getCoinName() {
    return this->coin_name;
}

double Coin::getCurrentPrice() {
    return this->price;
}

void Coin::addTradingExchange(Exchange* exchange) {
    // Add new exchange trading this coin
    this->trading_exchanges.insert(exchange);
}

unordered_set<Exchange*> Coin::getTradingExchanges() {
    return this->trading_exchanges;
}

void Coin::printStats() {
    cout << "-------------------------"           << endl;
    cout << "Coin stats:"                         << endl;
    cout << " -> Name: "                          << this->getCoinName() << endl;
    cout << " -> Current price: "                 << this->getCurrentPrice() << endl;
    cout << " -> Count of exchanges"              << this->getTradingExchanges().size() << endl;
    cout << " -> Total supply of coins: "         << this->total_supply << endl;
    cout << " -> Coins available for mining: "    << this->available_coins << endl;
    cout << " -> Coins in market (circulating): " << this->circulating_supply << endl;
    cout << "-------------------------"           << endl;
}
