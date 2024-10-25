#ifndef CRYPTO_EXCHANGE_H
#define CRYPTO_EXCHANGE_H

#include "crypto_coin.h"
#include "base_investor.h"

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
        double gov_taxes;
        Investor** customers;
        Coin* coin;

    public:
        Exchange(double fee, double init_coins, double gov_taxes, Investor** customers, Coin* coin);
        ~Exchange();

        double ExecuteTransaction(double amount, Investor* buyer, TransactionType type);
        void ClosingExchange();
        double getInterestRate();
        void UpdateGovTaxes(double new_value);
};

#endif // CRYPTO_EXCHANGE_H
