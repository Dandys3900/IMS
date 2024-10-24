#include "crypto_coin.h"

Coin::Coin(double initial_price, double total_supply, double circulating_suply)
    : price(initial_price),
      total_supply(total_supply),
      circulating_supply(circulating_suply)
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

double Coin::getCurrentPrice() {
    return this->price;
}
