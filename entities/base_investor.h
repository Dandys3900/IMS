#ifndef BASE_INVESTOR_H
#define BASE_INVESTOR_H

#include "includes.h"

/**
 * Base class for investors
*/
class Investor : public Process {
    private:
        double balance;

    public:
        Investor(double initial_balance)
            : balance(initial_balance)
        {
        }

        virtual ~Investor()
        {
        }

        virtual void Behavior()               = 0;
        virtual void BuyCoins(double amount)  = 0;
        virtual void SellCoins(double amount) = 0;
        virtual void ExchangeClosedReaction() = 0;
};

#endif // BASE_INVESTOR_H
