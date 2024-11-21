#include "crypto_miner.h"
#include "tech_devs.h"

TechDeveloper::TechDeveloper(double efficiency_boost, vector<CryptoMiner*> miners)
    : efficiency_boost(efficiency_boost),
      miners(miners)
{
}

TechDeveloper::~TechDeveloper() {

}

void TechDeveloper::Behavior() {
    while (true) {
        // Randomly select crypto miner which efficiency will be boosted
        int miner_index = static_cast<int>(Uniform(0, this->miners.size()));

        this->miners.at(miner_index)->SetMiningEfficiency(
            this->efficiency_boost
        );

        // Repeat every 6 months
        Wait(HALF_YEAR);
    }
}
