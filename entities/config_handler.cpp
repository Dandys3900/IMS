#include "crypto_coin.h"
#include "crypto_investor.h"
#include "crypto_miner.h"
#include "government.h"
#include "crypto_exchange.h"
#include "elon_tweet.h"
#include "tech_devs.h"
#include "config_handler.h"

// Define static member
string ConfigHandler::price_vals_file_name;

#define ENSURE(expression)\
if (!(expression)) {\
    return false;\
}

ConfigHandler::ConfigHandler() {}

ConfigHandler::~ConfigHandler() {
    freeSet(this->exchanges);
}

bool ConfigHandler::InitSimulation(string config_file_name) {
    // Load simulation config from JSON file
    ifstream config_file(config_file_name);
    json config = json::parse(config_file);

    // Clear file for storing coins price change over time
    price_vals_file_name = config_file_name.substr(0, config_file_name.rfind(".")) + string(".price_vals");
    ofstream price_file(price_vals_file_name, ios::trunc);
    price_file.close();
    
    // DO NOT CHANGE THE ORDER OF READINGS - some objects are dependent on others being validated first
    ENSURE(this->ReadConfigHead(config));
    ENSURE(this->ReadGovernment(config));
    ENSURE(this->ReadCoins(config));
    ENSURE(this->ReadElonTweeters(config));
    ENSURE(this->ReadInvestors(config));
    ENSURE(this->ReadMiners(config));
    ENSURE(this->ReadExchanges(config));
    ENSURE(this->ReadDevelopers(config));

    return true;
}


bool ConfigHandler::ReadConfigHead(json& json_object) {
    ENSURE(json_object.is_object());
    ENSURE(json_object.contains("simulation_duration_years") && json_object.at("simulation_duration_years").is_number());
    
    double simulation_duration_years = (double)json_object.at("simulation_duration_years");
    ENSURE(simulation_duration_years > 0.0);

    Init(0, simulation_duration_years * YEAR);
    return true;
}

bool ConfigHandler::ReadGovernment(json& json_object) {
    ENSURE(json_object.is_object());
    ENSURE(json_object.contains("government") && json_object.at("government").is_object());
    json& government = json_object.at("government");
    ENSURE(government.contains("initial_taxes") && government.at("initial_taxes").is_number());

    double initial_taxes = (double)government.at("initial_taxes");
    ENSURE(initial_taxes >= 0.0 && initial_taxes <= 1.0);
    
    this->government = new Government(initial_taxes, this->exchanges);
    return true;
}

bool ConfigHandler::ReadCoins(json& json_object) {
    ENSURE(json_object.is_object());
    ENSURE(json_object.contains("coins"));
    
    json& coins = json_object.at("coins");
    ENSURE(coins.is_array() && !coins.empty());
    for (json& coin : coins) {
        ENSURE(this->ReadCoin(coin));
    }
    return true;
}

bool ConfigHandler::ReadCoin(json& coin) {
    ENSURE(coin.is_object());
    ENSURE(coin.contains("name") && coin.at("name").is_string());
    ENSURE(coin.contains("initial_price") && coin.at("initial_price").is_number());
    ENSURE(coin.contains("mining_efficiency") && coin.at("mining_efficiency").is_number());
    ENSURE(coin.contains("total_supply") && coin.at("total_supply").is_number_integer());

    double initial_price = (double)coin.at("initial_price");
    double mining_efficiency = (double)coin.at("mining_efficiency");
    double total_supply = (double)coin.at("total_supply");

    ENSURE(initial_price > 0.0);    
    ENSURE(mining_efficiency > 0.0 && mining_efficiency <= 1.0);
    ENSURE(total_supply > 0.0);
      
    this->coins.push_back(
        new Coin(
            (string)coin.at("name"),
            initial_price,
            mining_efficiency,
            total_supply,
            0 // Calculate circulating_supply dynamically from config
        )
    );
    return true;
}

bool ConfigHandler::ReadExchanges(json& json_object) {
    ENSURE(json_object.is_object());
    ENSURE(json_object.contains("exchanges"));

    json& exchanges = json_object.at("exchanges");
    ENSURE(exchanges.is_array() && !exchanges.empty());
    for (json& exchange : exchanges) {
        ENSURE(this->ReadExchange(exchange));
    }
    return true;
}

bool ConfigHandler::ReadExchange(json& exchange) {
    vector<Coin*> traded_coins;
    CoinsStats initial_coin_amounts;

    ENSURE(exchange.is_object());
    ENSURE(exchange.contains("fee") && exchange.at("fee").is_number());
    ENSURE(exchange.contains("traded_coins") && exchange.at("traded_coins").is_array());

    for (json& traded_coin : exchange.at("traded_coins")) {
        ENSURE(traded_coin.contains("name") && traded_coin.at("name").is_string());
        ENSURE(traded_coin.contains("initial_amount") && traded_coin.at("initial_amount").is_number());

        string name = (string)traded_coin.at("name");
        double initial_amount = (double)traded_coin.at("initial_amount");

        ENSURE(initial_amount >= 0.0);

        // Make sure that the coin exists
        for (Coin* coin : this->coins) {
            if (coin->GetCoinName() == name) {
                traded_coins.push_back(coin);
                initial_coin_amounts.insert({name, initial_amount});
                coin->IncreaseSupply(initial_amount);
                break;
            }
        }
    }

    this->exchanges.push_back(
        new Exchange(
            (double)exchange.at("fee"),
            initial_coin_amounts,
            this->investors,
            traded_coins
        )
    );
    return true;
}

bool ConfigHandler::ReadInvestors(json& json_object) {
    ENSURE(json_object.is_object());
    if (!json_object.contains("investors")) {
        return true;
    }

    json& investors = json_object.at("investors");
    ENSURE(investors.is_array());
    for (json& investor : investors) {
        ENSURE(this->ReadInvestor(investor));
    }
    return true;
}

bool ConfigHandler::ReadInvestor(json& investor) {
    vector<Coin*> traded_coins;
    CoinsStats initial_coin_amounts;
    CoinsThresholds coin_thresholds;

    ENSURE(investor.is_object());
    ENSURE(investor.contains("type") && investor.at("type").is_string());
    ENSURE(investor.contains("traded_coins") && investor.at("traded_coins").is_array());
    
    ENSURE(investor.at("type") == "short_term" || investor.at("type") == "long_term");
    Investor::InvestorType investor_type = investor.at("type") == "short_term" ? Investor::InvestorType::SHORT_TERM : Investor::InvestorType::LONG_TERM;

    for (json& traded_coin : investor.at("traded_coins")) {
        ENSURE(traded_coin.contains("name") && traded_coin.at("name").is_string());
        ENSURE(traded_coin.contains("initial_amount") && traded_coin.at("initial_amount").is_number());
        ENSURE(traded_coin.contains("sell_threshold") && traded_coin.at("sell_threshold").is_number());
        ENSURE(traded_coin.contains("buy_threshold") && traded_coin.at("buy_threshold").is_number());

        string name = (string)traded_coin.at("name");
        double initial_amount = (double)traded_coin.at("initial_amount");
        double sell_threshold = (double)traded_coin.at("sell_threshold");
        double buy_threshold = (double)traded_coin.at("buy_threshold");

        ENSURE(initial_amount >= 0.0);
        ENSURE(sell_threshold >= 0.0);
        ENSURE(buy_threshold >= 0.0);
        ENSURE(buy_threshold < sell_threshold);

        // Make sure that the coin exists
        for (Coin* coin : this->coins) {
            if (coin->GetCoinName() == name) {
                traded_coins.push_back(coin);
                initial_coin_amounts.insert({name, initial_amount});
                coin_thresholds.insert({name, {sell_threshold, buy_threshold}});
                coin->IncreaseSupply(initial_amount);
                break;
            }
        }
    }

    this->investors.push_back(
        new Investor(
            investor_type,
            initial_coin_amounts,
            coin_thresholds,
            traded_coins
        )
    );
    return true;
}

bool ConfigHandler::ReadMiners(json& json_object) {
    ENSURE(json_object.is_object());
    if (!json_object.contains("miners")) {
        return true;
    }

    json& miners = json_object.at("miners");
    ENSURE(miners.is_array());
    for (json& miner : miners) {
        ENSURE(this->ReadMiner(miner));
    }
    return true;
}

bool ConfigHandler::ReadMiner(json& miner) {
    ENSURE(miner.is_object());
    ENSURE(miner.contains("intial_mining_rate_per_hour") && miner.at("intial_mining_rate_per_hour").is_number());
    ENSURE(miner.contains("hardware_performance") && miner.at("hardware_performance").is_number());
    ENSURE(miner.contains("mining_strategy") && miner.at("mining_strategy").is_string());
    ENSURE(miner.contains("mining_coins") && miner.at("mining_coins").is_array());
    double intial_mining_rate_per_hour = (double)miner.at("intial_mining_rate_per_hour");
    double hardware_performance = (double)miner.at("hardware_performance");
    string mining_strategy = (string)miner.at("mining_strategy");

    ENSURE(intial_mining_rate_per_hour > 0.0);
    ENSURE(hardware_performance > 0.0 && hardware_performance <= 1.0);
    ENSURE(mining_strategy == "random_choice" || mining_strategy == "best_choice");

    vector<Coin*> mining_coins;
    for (json& mining_coin : miner.at("mining_coins")) {
        ENSURE(mining_coin.is_string());
        // Make sure that the coin exists
        for (Coin* coin : this->coins) {
            if (coin->GetCoinName() == (string)mining_coin) {
                mining_coins.push_back(coin);
                break;
            }
        }
    }

    this->miners.push_back(
        new CryptoMiner(
            intial_mining_rate_per_hour,
            hardware_performance,
            mining_coins,
            mining_strategy
        )
    );
    return true;
}

bool ConfigHandler::ReadDevelopers(json& json_object) {
    ENSURE(json_object.is_object());
    if (!json_object.contains("tech_developers")) {
        return true;
    }
    
    json& tech_developers = json_object.at("tech_developers");
    ENSURE(tech_developers.is_array());
    for (json& tech_developer : tech_developers) {
        ENSURE(this->ReadDeveloper(tech_developer));
    }
    return true;
}

bool ConfigHandler::ReadDeveloper(json& developer) {
    ENSURE(developer.is_object());
    ENSURE(developer.contains("mining_performance_boost") && developer.at("mining_performance_boost").is_number());

    double mining_performance_boost = (double)developer.at("mining_performance_boost");
    
    ENSURE(mining_performance_boost > 0.0);

    this->tech_devs.push_back(new TechDeveloper(mining_performance_boost, this->miners));
    return true;
}

bool ConfigHandler::ReadElonTweeters(json& json_object) {
    ENSURE(json_object.is_object());
    if (!json_object.contains("elon_tweeters")) {
        return true;
    }
    
    json& elon_tweeters = json_object.at("elon_tweeters");
    ENSURE(elon_tweeters.is_array());
    for (json& elon_tweeter : elon_tweeters) {
        ENSURE(this->ReadElonTweeter(elon_tweeter));
    }
    return true;
}

bool ConfigHandler::ReadElonTweeter(json& elon_tweeter) {
    ENSURE(elon_tweeter.is_object());
    ENSURE(elon_tweeter.contains("affected_coin") && elon_tweeter.at("affected_coin").is_string());

    string affected_coin = (string)elon_tweeter.at("affected_coin");
    if (affected_coin == "random" && !this->coins.empty()) {
        // Randomly select coin which will Elon affect
        int coin_index = static_cast<int>(Uniform(0, this->coins.size()));
        this->elons.push_back(new ElonTweet(this->coins.at(coin_index)));
        return true;
    }

    // Ensure the coin exists
    for (Coin* coin : this->coins) {
        if (coin->GetCoinName() == affected_coin) {
            this->elons.push_back(new ElonTweet(coin));
            return true;
        }
    }
    return false;
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
