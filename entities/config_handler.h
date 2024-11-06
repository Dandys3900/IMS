#ifndef CONFHANDLER_H
#define CONFHANDLER_H

/***** SIMULATION ENTITIES *****/
#include "crypto_coin.h"
#include "base_investor.h"
#include "longterm_investor.h"
#include "shortterm_investor.h"
#include "crypto_miner.h"
#include "government.h"
#include "crypto_exchange.h"
#include "elon_tweet.h"
#include "tech_devs.h"

#include "includes.h"
#include "../json_parser/json.hpp"

using json = nlohmann::json;

class ConfigHandler {
    private:
        json config;
        // Store created entities
        unordered_set<Investor*> investors;
        unordered_set<Exchange*> exchanges;
        unordered_set<CryptoMiner*> miners;
        unordered_set<ElonTweet*> elons;
        unordered_set<Government*> governments;
        unordered_set<TechDeveloper*> tech_devs;

    public:
        ConfigHandler();
        ~ConfigHandler();

        void InitSimulation();
        void ClearSimulation();
};

#endif // CONFHANDLER_H
