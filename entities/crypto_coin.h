#ifndef CRYPTOCOIN_H
#define CRYPTOCOIN_H

#include "includes.h"

class Coin {
    private:
        double price;
        double total_supply;
        double circulating_supply;

    public:
        Coin(double initial_price, double total_supply, double circulating_suply);
        ~Coin();

        void IncreaseSupply(double amount);
        void DecreaseSupply(double amount);
        void IncreasePrice(double factor);
        void DecreasePrice(double factor);
        void UpdatePrice();
        double getCurrentPrice();
};

#endif // CRYPTOCOIN_H
