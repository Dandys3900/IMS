#ifndef CRYPTOCOIN_H
#define CRYPTOCOIN_H

#include "includes.h"

class Investor;
class Exchange;

class Coin : public Process {
    private:
        const string coin_name;      // Unique name of coin
        double price;
        double mining_efficiency;    // Each coin is mined in different way, with different algorithms
        double total_supply;         // circulating_supply + available_coins
        double circulating_supply;   // Coins that someone holds
        double available_coins;      // Coins available for mining
        vector<Investor*> traders;   // List of investors trading this coin
        vector<Exchange*> exchanges; // List of exchanges trading this coin
        vector<double> price_history;// List storing crypto coin price for each simulation day

    public:
        Coin(const string coin_name, double initial_price, double mining_efficiency, double total_supply, double circulating_supply);
        ~Coin();

        void Behavior() override;
        void IncreaseSupply(double amount);
        void DecreaseSupply(double amount);
        void ChangePrice(double factor);
        void UpdatePrice();
        double MineCoins(double amount);
        const string GetCoinName();
        double GetCurrentPrice();
        double GetMiningEfficiency();
        void AddTrader(Investor* investor);
        vector<Exchange*> GetExchanges();
        void AddExchange(Exchange* exchange);
        vector<Investor*> GetTraders();
        vector<double> GetPriceHistory();
        void PrintStats();
};

#endif // CRYPTOCOIN_H
