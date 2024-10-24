#ifndef ELONTWEET_H
#define ELONTWEET_H

#include "includes.h"

class ElonTweet : public Event {
    private:
        Coin* coin;

    public:
        ElonTweet(Coin* coin);
        ~ElonTweet();

        void Behavior() override;
};

#endif // ELONTWEET_H
