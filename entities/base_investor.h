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
        Investor(CoinsStats initial_balance, CoinsThresholds thresholds, vector<Coin*> coins)
            : balance(initial_balance),
              thresholds(thresholds),
              coins(coins),
              sentiment(0.0)
        {
            // Link investor with coins
            for (auto coin : this->coins)
                coin->AddTrader(this);
        }

        virtual ~Investor()
        {
        }

        virtual void BuyCoins(double amount, Coin* coin)  = 0;
        virtual void SellCoins(double amount, Coin* coin) = 0;

        void PositiveNewsReaction() {
            // Results in higher investor sentiment value affected by good news
            // Randomly select how affected this investor is
            this->sentiment = Uniform(0.0, 1.0);
        }

        void NegativeNewsReaction() {
            // Results in lowering investor sentiment value affected by bad news
            // Randomly select how affected this investor is
            this->sentiment = Uniform(-1.0, 0.0);
        }

        double GetInvestorSentiment() {
            return this->sentiment;
        }

        void PrintStats() {
            cout << "-------------------------" << endl;
            cout << "Investor stats:"           << endl;
            cout << " -> Traided coins: "       << endl;
            for (auto coin : this->coins) {
                string coinname = coin->GetCoinName();
                cout << "Name: " << coinname << " final balance: " << this->balance.at(coinname) << endl;
                cout << "Sell threshold: " << this->thresholds.at(coinname).first << endl;
                cout << "Buy threshold: " << this->thresholds.at(coinname).second << endl;
            }
            cout << "-------------------------" << endl;
        }
};

#endif // BASE_INVESTOR_H
