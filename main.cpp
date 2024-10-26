#include "entities/includes.h"
#include "json_parser/json.hpp"

/***** SIMULATION ENTITIES *****/
#include "entities/crypto_coin.h"
#include "entities/base_investor.h"
#include "entities/longterm_investor.h"
#include "entities/shortterm_investor.h"
#include "entities/crypto_miner.h"
#include "entities/government.h"
#include "entities/crypto_exchange.h"
#include "entities/elon_tweet.h"
#include "entities/tech_devs.h"

using json = nlohmann::json;

template <typename T>
void freeSet(std::unordered_set<T*>& set) {
    // Properly free set pointers
    for (T* ptr : set) {
        delete ptr;
    }
    // Clear set itself
    set.clear();
}

int main (int argc, char *argv[]) {
    // Load simulation config from JSON file
    std::ifstream config_file("sim_config.json");
    json sim_config = json::parse(config_file);

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

    unordered_set<CryptoMiner*> miners = {
        miner
    };
    TechDeveloper* techdev = new TechDeveloper(1.2, miners);
    techdev->Activate();

    unordered_set<Investor*> customers = {
        long_investor,
        short_investor
    };
    Exchange* exchange = new Exchange(0.01, 2500, 0.15, customers, coin);

    unordered_set<Exchange*> exchanges = {
        exchange
    };
    Government* government = new Government(0.15, exchanges);
    government->Activate();

    ElonTweet* elon_tweet = new ElonTweet(coin);
    elon_tweet->Activate();

    Run();

    // Output simulation statistics
    SIMLIB_statistics.Output();

    // Cleanup
    delete elon_tweet;
    delete government;
    freeSet(exchanges);
    freeSet(customers);
    delete techdev;
    freeSet(miners);
    delete coin;

    return EXIT_SUCCESS;
}
