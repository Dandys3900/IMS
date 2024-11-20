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
        unordered_set<Coin*> coins;

    public:
        Investor(CoinsStats initial_balance, CoinsThresholds thresholds, unordered_set<Coin*> coins)
            : balance(initial_balance),
              thresholds(thresholds),
              coins(coins)
        {
        }

        virtual ~Investor()
        {
        }

        virtual void BuyCoins(double amount, Coin* coin)  = 0;
        virtual void SellCoins(double amount, Coin* coin) = 0;
        virtual void ExchangeClosedReaction() = 0;

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
