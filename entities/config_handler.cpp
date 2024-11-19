#include "crypto_coin.h"
#include "base_investor.h"
#include "longterm_investor.h"
#include "shortterm_investor.h"
#include "crypto_miner.h"
#include "government.h"
#include "crypto_exchange.h"
#include "elon_tweet.h"
#include "tech_devs.h"
#include "config_handler.h"

ConfigHandler::ConfigHandler() {
    // Load simulation config from JSON file
    std::ifstream config_file("sim_config.json");
    this->config = json::parse(config_file);
}

ConfigHandler::~ConfigHandler() {
    // Cleanup
    delete this->government;
    freeSet(this->coins);
    freeSet(this->investors);
    freeSet(this->exchanges);
    freeSet(this->miners);
    freeSet(this->elons);
    freeSet(this->tech_devs);
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
            this->coins.insert(
                new Coin(
                    (string)entity.at("name"),
                    (double)entity.at("initial_price"),
                    (double)entity.at("total_supply"),
                    (double)entity.at("circulating_supply")
                )
            );
        }
        else if (entity_name == "investor_longterm" || entity_name == "investor_shortterm") {
            // Create set of coins trader will trade
            unordered_set<Coin*> coins;
            CoinsStats stats;
            CoinsThresholds thresholds;

            for (auto coin : entity.at("coins")) {
                // Get coin info (name, count)
                const auto coininfo = coin.begin();
                // Find coin matching given coin name
                for (auto coin : this->coins) {
                    if (coin->getCoinName() == (string)coininfo.key()) {
                        coins.insert(coin);
                        stats.insert({(string)coininfo.key(), (double)coininfo.value()});
                    }
                }
                // Add threshold for this coin (coinname, sell and buy thresholds)
                thresholds.insert({
                    (string)coininfo.key(), {
                        (double)coin.at("sell_threshold"),
                        (double)coin.at("buy_threshold")
                    }
                });
            }

            if (entity_name == "investor_longterm")
                this->investors.insert(
                    new LongTermInvestor(
                        stats,
                        thresholds,
                        coins
                    )
                );
            else // investor_shortterm
                this->investors.insert(
                    new ShortTermInvestor(
                        stats,
                        thresholds,
                        coins
                    )
                );
        }
        else if (entity_name == "exchange") {
            // Create set of coins exchange will trade
            unordered_set<Coin*> coins;
            CoinsStats stats;

            for (auto [key, value] : entity.at("initial_coin_amount").items()) {
                for (auto coin : this->coins) {
                    if (coin->getCoinName() == (string)key) {
                        coins.insert(coin);
                        stats.insert({(string)key, (double)value});
                    }
                }
            }

            this->exchanges.insert(
                new Exchange(
                    (double)entity.at("fee"),
                    stats,
                    (double)entity.at("gov_taxes"),
                    this->investors,
                    coins
                )
            );
        }
        else if (entity_name == "government") {
            this->government = new Government(
                (double)entity.at("init_taxes"),
                this->exchanges
            );
        }
        else if (entity_name == "miner") {
            // Create set of coins miner will mine
            unordered_set<Coin*> coins;

            for (auto targetcoin : entity.at("coins")) {
                for (auto coin : this->coins) {
                    if (coin->getCoinName() == (string)targetcoin)
                        coins.insert(coin);
                }
            }

            this->miners.insert(
                new CryptoMiner(
                    (double)entity.at("intial_mining_rate_per_hour"),
                    (double)entity.at("initial_effeciency"),
                    coins
                )
            );
        }
        else if (entity_name == "elon_tweeter") {
            this->elons.insert(
                new ElonTweet(
                    // Use first coin by default, TODO: Change this
                    *(this->coins.begin())
                )
            );
        }
        else if (entity_name == "tech_dev") {
            this->tech_devs.insert(
                new TechDeveloper(
                    (double)entity.at("mining_efficiency_boost"),
                    this->miners
                )
            );
        }
        else
            throw ProgramException("Invalid entity type: " + (string)entity.at("type"));
    }
}

template <typename T>
void ConfigHandler::freeSet(std::unordered_set<T*>& set) {
    // Properly free set pointers
    for (T* ptr : set)
        delete ptr;
    // Clear set itself
    set.clear();
}
