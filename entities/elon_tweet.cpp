#include "crypto_coin.h"
#include "elon_tweet.h"

ElonTweet::ElonTweet(Coin* coin)
    : coin(coin),
      done_changes("")
{
}

ElonTweet::~ElonTweet() {
    this->PrintStats();
}

void ElonTweet::Behavior() {
    while (true) {
        // Repeat every 2-8 month
        Wait(Uniform(2 * EACH_MONTH, 8 * EACH_MONTH));

        // Randomly select factor of price change (according to study between <-11.8% , +16.9%))
        double change_factor = Uniform(-0.118, 0.169);

        // Change coin's price
        coin->ChangePrice(change_factor);
        // Store record about this change
        done_changes += "Change price about " + to_string(change_factor * 100) + " %" + "\n";
    }
}

void ElonTweet::PrintStats() {
    cout << "-------------------------" << endl;
    cout << "Unpredicted price change stats (aka Elon tweet):" << endl;
    cout << this->done_changes << endl;
    cout << "-------------------------" << endl;
}
