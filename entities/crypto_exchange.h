#ifndef CRYPTO_EXCHANGE_H
#define CRYPTO_EXCHANGE_H

#include "includes.h"

class Coin;
class Investor;

class Exchange : public Facility {
    private:
        double transaction_fee;
        CoinsStats initial_coins;
        double sold_coins;
        CoinsStats stacked_coins;
        double gov_taxes;
        vector<Investor*> customers;
        vector<Coin*> coins;
        bool closed_by_gov;

    public:
        Exchange(double fee, CoinsStats init_coins, vector<Investor*> customers, vector<Coin*> coins);
        ~Exchange();

        double BuyCoins(Coin* coin, double amount);
        double SellCoins(Coin* coin, double amount);
        void ClosingExchange();
        double GetInterestRate(const string coin_name);
        double GetTotalFeeFactor();
        void UpdateGovTaxes(double new_value);
        bool IsClosed();
        bool HasCoins(Coin* coin);
        void PrintStats();

        static Exchange* SelectRandomExchangeFor(Coin* coin);
        static Exchange* SelectBestExchangeFor(Coin* coin);
};

#endif // CRYPTO_EXCHANGE_H
