#include "entities/includes.h"

int main (int argc, char *argv[]) {
    // Simulate for 1 year
    Init(0, 365);

    // Set total amount of coins in simulation and randomly diverse them between entities and exchanges
    Coin* coin = new Coin(1000, 1000000, 5000);

    LongTermInvestor* long_investor = new LongTermInvestor(2000, coin);
    long_investor->Activate();

    ShortTermInvestor* short_investor = new ShortTermInvestor(500, coin);
    short_investor->Activate();

    CryptoMiner* miner = new CryptoMiner(10, 100, coin);
    miner->Activate();

    Investor* customers[] = {long_investor, short_investor};
    Exchange* exchange = new Exchange(0.01, 2500, customers, coin);

    Exchange* exchanges[] = {exchange};
    Government* government = new Government(exchanges);
    government->Activate();

    ElonTweet* elon_tweet = new ElonTweet(coin);
    elon_tweet->Activate();

    Run();

    // Output simulation statistics
    SIMLIB_statistics.Output();

    return EXIT_SUCCESS;
}
