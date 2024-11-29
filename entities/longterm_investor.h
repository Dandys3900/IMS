#ifndef LONGTERM_INVESTOR_H
#define LONGTERM_INVESTOR_H

#include "base_investor.h"

/**
 * Class for long-term investor
 *  Regularily buys coins and keeps them.
*/
class LongTermInvestor : public Investor {
    public:
        LongTermInvestor(CoinsStats initial_balance, CoinsThresholds thresholds, vector<Coin*> coins);
        ~LongTermInvestor();

        void Behavior() override;
        void BuyCoins(Coin* coin)  override;
        void SellCoins(Coin* coin) override;
};

#endif // LONGTERM_INVESTOR_H
