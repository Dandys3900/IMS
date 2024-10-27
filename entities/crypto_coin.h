#ifndef CRYPTOCOIN_H
#define CRYPTOCOIN_H

class Coin {
    private:
        double price;
        double total_supply;       // circulating_supply + available_coins
        double circulating_supply; // Coins that someone holds
        double available_coins;    // Coins available for mining

    public:
        Coin(double initial_price, double total_supply, double circulating_supply);
        ~Coin();

        void IncreaseSupply(double amount);
        void DecreaseSupply(double amount);
        void IncreasePrice(double factor);
        void DecreasePrice(double factor);
        void UpdatePrice();
        double MineCoins(double amount);
        double getCurrentPrice();
};

#endif // CRYPTOCOIN_H
