#ifndef SHORTTERM_INVESTOR_H
#define SHORTTERM_INVESTOR_H

#include "base_investor.h"

/**
 * Class for short-term investor
 *  Highly affected by current market prices, randomly buys and sells coins.
*/
class ShortTermInvestor : public Investor {
    public:
        ShortTermInvestor(CoinsStats initial_balance, CoinsThresholds thresholds, vector<Coin*> coins);
        ~ShortTermInvestor();

        void Behavior() override;
        void BuyCoins(Coin* coin)  override;
        void SellCoins(Coin* coin) override;
};

#endif // SHORTTERM_INVESTOR_H
