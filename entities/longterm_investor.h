#ifndef LONGTERM_INVESTOR_H
#define LONGTERM_INVESTOR_H

#include "base_investor.h"

/**
 * Class for long-term investor
 *  Regularily buys coins and keeps them.
*/
class LongTermInvestor : public Investor {
    public:
        LongTermInvestor(CoinsStats initial_balance, unordered_set<Coin*> coins);
        ~LongTermInvestor();

        void Behavior() override;
        void BuyCoins(double amount, Coin* coin)  override;
        void SellCoins(double amount, Coin* coin) override;
        void ExchangeClosedReaction() override;
};

#endif // LONGTERM_INVESTOR_H
