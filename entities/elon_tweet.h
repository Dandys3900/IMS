#ifndef ELONTWEET_H
#define ELONTWEET_H

#include "includes.h"

class Coin;

class ElonTweet : public Process {
    private:
        Coin* coin;

    public:
        ElonTweet(Coin* coin);
        ~ElonTweet();

        void Behavior() override;
};

#endif // ELONTWEET_H
