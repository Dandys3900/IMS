#include "crypto_coin.h"
#include "crypto_investor.h"
#include "crypto_miner.h"
#include "government.h"
#include "crypto_exchange.h"
#include "elon_tweet.h"
#include "tech_devs.h"
#include "config_handler.h"

ConfigHandler::ConfigHandler() {
    // Load simulation config from JSON file
    ifstream config_file("sim_config.json");
    this->config = json::parse(config_file);

    // Clear file for storing coins price change over time
    ofstream price_file("price_vals", ios::trunc);
    price_file.close();
}

ConfigHandler::~ConfigHandler() {
    freeSet(this->exchanges);
}

void ConfigHandler::InitSimulation() {
    // Iterate over JSON array and create requested entities
    for (auto entity : this->config) {
        // Determine entity type
        string entity_name = entity.at("type");

        if (entity_name == "sim_duration") {
            // Load given simulation duration (in years)
            Init(0, (double)entity.at("sim_duration_years") * YEAR);
        }
        else if (entity_name == "coin") {
            this->coins.push_back(
                new Coin(
                    (string)entity.at("name"),
                    (double)entity.at("initial_price"),
                    (double)entity.at("mining_efficiency"),
                    (double)entity.at("total_supply"),
                    (double)entity.at("circulating_supply")
                )
            );
        }
        else if (entity_name == "investor_longterm" || entity_name == "investor_shortterm") {
            // Create set of coins trader will trade
            vector<Coin*> coins;
            CoinsStats stats;
            CoinsThresholds thresholds;

            for (auto coin : entity.at("coins")) {
                for (auto coin_data : coin.items()) {
                    // Extract key from each dictionary record
                    string key = coin_data.key();
                    // Get coin info (name, count)
                    if (key != "sell_threshold" && key != "buy_threshold") {
                        if (this->coins.empty())
                            throw ("Missing coins for investor, can't proceed");

                        // Find coin matching given coin name
                        for (auto coin : this->coins) {
                            if (coin->GetCoinName() == key) {
                                coins.push_back(coin);
                                stats.insert({key, (double)coin_data.value()});
                            }
                        }
                        // Add threshold for this coin (coinname, sell and buy thresholds)
                        thresholds.insert({
                            key, {
                                (double)coin.at("sell_threshold"),
                                (double)coin.at("buy_threshold")
                            }
                        });
                        break;
                    }
                }
            }

            if (entity_name == "investor_longterm")
                this->investors.push_back(
                    new Investor(
                        Investor::InvestorType::LONG_TERM,
                        stats,
                        thresholds,
                        coins
                    )
                );
            else // investor_shortterm
                this->investors.push_back(
                    new Investor(
                        Investor::InvestorType::SHORT_TERM,
                        stats,
                        thresholds,
                        coins
                    )
                );
        }
        else if (entity_name == "exchange") {
            // Create set of coins exchange will trade
            vector<Coin*> coins;
            CoinsStats stats;

            for (auto [key, value] : entity.at("initial_coin_amount").items()) {
                if (this->coins.empty())
                    throw ("Missing coins for exchange, can't proceed");

                for (auto coin : this->coins) {
                    if (coin->GetCoinName() == (string)key) {
                        coins.push_back(coin);
                        stats.insert({(string)key, (double)value});
                    }
                }
            }

            this->exchanges.push_back(
                new Exchange(
                    (double)entity.at("fee"),
                    stats,
                    this->investors,
                    coins
                )
            );
        }
        else if (entity_name == "government") {
            if (this->exchanges.empty())
                throw ("Missing exchanges for government, can't proceed");

            this->government = new Government(
                (double)entity.at("init_taxes"),
                this->exchanges
            );
            // Populate government taxes for all exchanges
            for (auto exchange : this->exchanges)
                exchange->UpdateGovTaxes(this->government->GetCurrentTaxes());
        }
        else if (entity_name == "miner") {
            // Create set of coins miner will mine
            vector<Coin*> coins;

            for (auto targetcoin : entity.at("coins")) {
                if (this->coins.empty())
                    throw ("Missing coins for miner, can't proceed");

                for (auto coin : this->coins) {
                    if (coin->GetCoinName() == (string)targetcoin)
                        coins.push_back(coin);
                }
            }

            this->miners.push_back(
                new CryptoMiner(
                    (double)entity.at("intial_mining_rate_per_hour"),
                    (double)entity.at("hardware_performance"),
                    coins,
                    (string)entity.at("mining_strategy")
                )
            );
        }
        else if (entity_name == "elon_tweeter") {
            if (this->coins.empty())
                throw ("Missing coins for random price change (Elon), can't proceed");

            // Randomly select coin which will Elon affect
            int coin_index = static_cast<int>(Uniform(0, this->coins.size()));

            this->elons.push_back(
                new ElonTweet(
                    this->coins.at(coin_index)
                )
            );
        }
        else if (entity_name == "tech_dev") {
            if (this->miners.empty())
                throw ("Missing miners for tech devs, can't proceed");

            this->tech_devs.push_back(
                new TechDeveloper(
                    (double)entity.at("mining_performance_boost"),
                    this->miners
                )
            );
        }
        else
            throw ("Invalid entity type: " + (string)entity.at("type"));
    }
}

void ConfigHandler::ActivateSimulation() {
    // Activate each entity in vectors
    for (auto coin : this->coins)
        coin->Activate();
    for (auto investor : this->investors)
        investor->Activate();
    for (auto miner : this->miners)
        miner->Activate();
    for (auto elon : this->elons)
        elon->Activate();
    for (auto tech_dev : this->tech_devs)
        tech_dev->Activate();
    if (this->government)
        this->government->Activate();
}

template <typename T>
void ConfigHandler::freeSet(std::vector<T*>& set) {
    // Properly free set pointers
    for (T* ptr : set)
        delete ptr;
    // Clear set itself
    set.clear();
}
