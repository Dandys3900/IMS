#ifndef SHORTTERM_INVESTOR_H
#define SHORTTERM_INVESTOR_H

#include "base_investor.h"

/**
 * Class for short-term investor
 *  Highly affected by current market prices, randomly buys and sells coins.
*/
class ShortTermInvestor : public Investor {
    public:
        ShortTermInvestor(CoinsStats initial_balance, unordered_set<Coin*> coins);
        ~ShortTermInvestor();

        void Behavior() override;
        void BuyCoins(double amount, Coin* coin)  override;
        void SellCoins(double amount, Coin* coin) override;
        void ExchangeClosedReaction() override;
};

#endif // SHORTTERM_INVESTOR_H
