#ifndef BASE_INVESTOR_H
#define BASE_INVESTOR_H

#include "crypto_coin.h"
#include <simlib.h>

/**
 * Base class for investors
*/
class Investor : public Process {
    private:
        double balance;
        Coin* coin;

    public:
        Investor(double initial_balance, Coin* coin)
            : balance(initial_balance),
              coin(coin)
        {
        }

        virtual ~Investor()
        {
        }

        virtual void BuyCoins(double amount)  = 0;
        virtual void SellCoins(double amount) = 0;
        virtual void ExchangeClosedReaction() = 0;
};

#endif // BASE_INVESTOR_H
