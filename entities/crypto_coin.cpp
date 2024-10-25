#include "crypto_coin.h"

Coin::Coin(double initial_price, double total_supply, double circulating_supply)
    : price(initial_price),
      total_supply(total_supply),
      circulating_supply(circulating_supply),
      available_coins(total_supply - circulating_supply)
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

double Coin::getCurrentPrice() {
    return this->price;
}
