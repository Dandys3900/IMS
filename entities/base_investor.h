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
        unordered_set<Coin*> coins;

    public:
        Investor(CoinsStats initial_balance, unordered_set<Coin*> coins)
            : balance(initial_balance),
              coins(coins)
        {
        }

        virtual ~Investor()
        {
        }

        virtual void BuyCoins(double amount, Coin* coin)  = 0;
        virtual void SellCoins(double amount, Coin* coin) = 0;
        virtual void ExchangeClosedReaction() = 0;

        void printStats() {
            cout << "-------------------------" << endl;
            cout << "Investor stats:"           << endl;
            cout << " -> Traided coins: "       << endl;
            for (auto coin : this->coins) {
                string coinname = coin->getCoinName();
                cout << "Name: " << coinname << " final balance: " << this->balance.at(coinname) << endl;
            }
            cout << "-------------------------" << endl;
        }
};

#endif // BASE_INVESTOR_H
