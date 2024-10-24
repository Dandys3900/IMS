#ifndef CRYPTO_EXCHANGE_H
#define CRYPTO_EXCHANGE_H

#include "includes.h"

// Transaction types
enum TransactionType {
    BUY,
    SELL
};

class Exchange : public Facility {
    private:
        double transaction_fee;
        double initial_coins;
        double sold_coins;
        double stacked_coins;
        Investor** customers;
        Coin* coin;

    public:
        Exchange(double fee, double init_coins, Investor** customers, Coin* coin);
        ~Exchange();

        void ExecuteTransaction(double amount, Investor* buyer, TransactionType type);
        void ClosingExchange();
        double getInterestRate();
};

#endif // CRYPTO_EXCHANGE_H
