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
        unordered_set<Investor*> customers;
        unordered_set<Coin*> coins;
        bool closed_by_gov;

    public:
        Exchange(double fee, CoinsStats init_coins, double gov_taxes, unordered_set<Investor*> customers, unordered_set<Coin*> coins);
        ~Exchange();

        double ExecuteTransaction(double amount, Investor* buyer, Coin* coin, TransactionType type);
        void ClosingExchange();
        double getInterestRate();
        void UpdateGovTaxes(double new_value);
        void printStats();
};

#endif // CRYPTO_EXCHANGE_H
