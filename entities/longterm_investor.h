#ifndef LONGTERM_INVESTOR_H
#define LONGTERM_INVESTOR_H

#include "base_investor.h"

/**
 * Class for long-term investor
 *  Regularily buys coins and keeps them.
*/
class LongTermInvestor : public Investor {
    public:
        LongTermInvestor(double initial_balance, Coin* coin);
        ~LongTermInvestor();

        void Behavior()               override;
        void BuyCoins(double amount)  override;
        void SellCoins(double amount) override;
        void ExchangeClosedReaction() override;
};

#endif // LONGTERM_INVESTOR_H
