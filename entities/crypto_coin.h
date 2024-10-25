#ifndef CRYPTOCOIN_H
#define CRYPTOCOIN_H

class Coin {
    private:
        double price;
        double total_supply;
        double circulating_supply;
        // Coins available for mining
        double available_coins;

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
