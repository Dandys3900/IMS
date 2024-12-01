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
    public:
        static string price_vals_file_name;

    private:
        // Store created entities
        vector<Coin*> coins;
        vector<Investor*> investors;
        vector<Exchange*> exchanges;
        vector<CryptoMiner*> miners;
        vector<ElonTweet*> elons;
        vector<TechDeveloper*> tech_devs;
        Government* government = nullptr;

        template <typename T>
        void freeSet(std::vector<T*>& set);

    public:
        ConfigHandler();
        ~ConfigHandler();

        void InitSimulation(string config_file);
        void ActivateSimulation();
};

#endif // CONF_HANDLER_H
