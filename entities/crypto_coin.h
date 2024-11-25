#ifndef CRYPTOCOIN_H
#define CRYPTOCOIN_H

#include "includes.h"

class Investor;
class Exchange;

class Coin {
    private:
        const string coin_name;      // Unique name of coin
        double price;
        double mining_efficiency;    // Each coin is mined in different way, with different algorithms
        double total_supply;         // circulating_supply + available_coins
        double circulating_supply;   // Coins that someone holds
        double available_coins;      // Coins available for mining
        vector<Investor*> traders;   // List of investors trading this coin
        vector<Exchange*> exchanges; // List of exchanges trading this coin

    public:
        Coin(const string coin_name, double initial_price, double mining_efficiency, double total_supply, double circulating_supply);
        ~Coin();

        void IncreaseSupply(double amount);
        void DecreaseSupply(double amount);
        void ChangePrice(double factor);
        void UpdatePrice();
        double MineCoins(double amount);
        const string GetCoinName();
        double GetCurrentPrice();
        double GetMiningEfficiency();
        void AddTrader(Investor* investor);
        void AddExchange(Exchange* exchange);
        vector<Investor*> GetTraders();
        void PrintStats();
};

#endif // CRYPTOCOIN_H
