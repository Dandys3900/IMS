#include "config_handler.h"

ConfigHandler::ConfigHandler() {
    // Load simulation config from JSON file
    std::ifstream config_file("sim_config.json");
    this->config = json::parse(config_file);
}

ConfigHandler::~ConfigHandler() {

}

void ConfigHandler::InitSimulation() {
    // Iterate over JSON array and create requested entities
    for (auto& [key, value] : this->config.items()) {
        std::cout << key << " : " << value << "\n";
    }
}

template <typename T>
void freeSet(std::unordered_set<T*>& set) {
    // Properly free set pointers
    for (T* ptr : set) {
        delete ptr;
    }
    // Clear set itself
    set.clear();
}

void ConfigHandler::ClearSimulation() {
    // Cleanup
    delete elon_tweet;
    delete government;
    freeSet(exchanges);
    freeSet(customers);
    delete techdev;
    freeSet(miners);
    delete coin;
}
