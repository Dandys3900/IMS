#ifndef CRYPTO_EXCHANGE_H
#define CRYPTO_EXCHANGE_H

#include "includes.h"

class Coin;
class Investor;

// Transaction types
enum TransactionType {
    BUY,
    SELL
};

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

        double ExecuteTransaction(double amount, Investor* buyer, Coin* coin, TransactionType type);
        void ClosingExchange();
        double GetInterestRate();
        void UpdateGovTaxes(double new_value);
        void PrintStats();
};

#endif // CRYPTO_EXCHANGE_H
