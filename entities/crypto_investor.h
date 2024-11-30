#ifndef INVESTOR_H
#define INVESTOR_H

#include "includes.h"

class Coin;

/**
 * Base class for investors
*/
class Investor : public Process {
	public:
		enum InvestorType {
			SHORT_TERM,
			LONG_TERM,
		};
	
    protected:
		InvestorType investor_type;
        CoinsStats balance;
        CoinsThresholds thresholds;
        vector<Coin*> coins;
        double sentiment;

    public:
        Investor(InvestorType investor_type, CoinsStats initial_balance, CoinsThresholds thresholds, vector<Coin*> coins);
        ~Investor();

		void Behavior() override;

        void BuyCoins(Coin* coin);
        void SellCoins(Coin* coin);

        void PositiveNewsReaction();
        void NegativeNewsReaction();
        double GetInvestorSentiment();
        void PrintStats();
};

#endif // BINVESTOR_H
