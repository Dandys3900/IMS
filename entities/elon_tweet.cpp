#include "crypto_coin.h"
#include "elon_tweet.h"

ElonTweet::ElonTweet(Coin* coin)
    : coin(coin)
{
}

ElonTweet::~ElonTweet() {

}

void ElonTweet::Behavior() {
    while (true) {
        // Randomly select factor of price change (according to study between <-11.8% , +16.9%>)
        double change_factor = Uniform(-0.118, 0.169);

        // Change coin's price
        coin->ChangePrice(change_factor);

        // Repeat every 2-8 month
        Wait(Uniform(2 * EACH_MONTH, 8 * EACH_MONTH));
    }
}
