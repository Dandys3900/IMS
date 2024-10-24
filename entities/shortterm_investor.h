#ifndef SHORTTERM_INVESTOR_H
#define SHORTTERM_INVESTOR_H

#include "base_investor.h"

/**
 * Class for short-term investor
 *  Highly affected by current market prices, randomly buys and sells coins.
*/
class ShortTermInvestor : public Investor {
    public:
        ShortTermInvestor(double initial_balance, Coin* coin);
        ~ShortTermInvestor();

        void Behavior()               override;
        void BuyCoins(double amount)  override;
        void SellCoins(double amount) override;
        void ExchangeClosedReaction() override;
};

#endif // SHORTTERM_INVESTOR_H
