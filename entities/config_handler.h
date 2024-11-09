#ifndef CONF_HANDLER_H
#define CONF_HANDLER_H

#include "includes.h"
#include "../json_parser/json.hpp"

class Coin;
class Investor;
class Exchange;
class CryptoMiner;
class ElonTweet;
class Government;
class TechDeveloper;

using json = nlohmann::json;

class ConfigHandler {
    private:
        json config;
        // Store created entities
        unordered_set<Coin*> coins;
        unordered_set<Investor*> investors;
        unordered_set<Exchange*> exchanges;
        unordered_set<CryptoMiner*> miners;
        unordered_set<ElonTweet*> elons;
        Government* government;
        unordered_set<TechDeveloper*> tech_devs;

        template <typename T>
        void freeSet(std::unordered_set<T*>& set);

    public:
        ConfigHandler();
        ~ConfigHandler();

        void InitSimulation();
};

#endif // CONF_HANDLER_H
