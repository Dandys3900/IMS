#ifndef CRYPTOCOIN_H
#define CRYPTOCOIN_H

#include "includes.h"

class Exchange;

class Coin {
    private:
        const string coin_name;    // Unique name of coin
        double price;
        double total_supply;       // circulating_supply + available_coins
        double circulating_supply; // Coins that someone holds
        double available_coins;    // Coins available for mining
        unordered_set<Exchange*> trading_exchanges; // List of exchanges trading this coin

    public:
        Coin(const string coin_name, double initial_price, double total_supply, double circulating_supply);
        ~Coin();

        void IncreaseSupply(double amount);
        void DecreaseSupply(double amount);
        void IncreasePrice(double factor);
        void DecreasePrice(double factor);
        void UpdatePrice();
        double MineCoins(double amount);
        const string getCoinName();
        double getCurrentPrice();
        void addTradingExchange(Exchange* exchange);
        unordered_set<Exchange*> getTradingExchanges();
        void printStats();
};

#endif // CRYPTOCOIN_H
