#include "crypto_coin.h"
#include "elon_tweet.h"

ElonTweet::ElonTweet(Coin* coin)
    : coin(coin)
{
}

ElonTweet::~ElonTweet() {

}

void ElonTweet::Behavior() {
    // At random time, either increase/decrease price of coin
}
