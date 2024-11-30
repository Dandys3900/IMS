#ifndef BASE_INVESTOR_H
#define BASE_INVESTOR_H

#include "includes.h"

class Coin;

/**
 * Base class for investors
*/
class Investor : public Process {
    protected:
        CoinsStats balance;
        CoinsThresholds thresholds;
        vector<Coin*> coins;
        double sentiment;

    public:
        Investor(CoinsStats initial_balance, CoinsThresholds thresholds, vector<Coin*> coins);
        virtual ~Investor() {
            this->PrintStats();
        }

        virtual void BuyCoins(double amount, Coin* coin)  = 0;
        virtual void SellCoins(double amount, Coin* coin) = 0;

        void PositiveNewsReaction();
        void NegativeNewsReaction();
        double GetInvestorSentiment();
        void PrintStats();
};

#endif // BASE_INVESTOR_H
