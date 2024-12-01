#ifndef ELONTWEET_H
#define ELONTWEET_H

#include "includes.h"

class Coin;

class ElonTweet : public Process {
    private:
        Coin* coin;
        string done_changes; // Document all price changes done by this class
        string selected_coin_name;

    public:
        ElonTweet(Coin* coin);
        ~ElonTweet();

        void Behavior() override;
        void PrintStats();
};

#endif // ELONTWEET_H
