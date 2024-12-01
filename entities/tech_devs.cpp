#include "crypto_miner.h"
#include "tech_devs.h"

TechDeveloper::TechDeveloper(double performance_boost, vector<CryptoMiner*> miners)
    : performance_boost(performance_boost),
      miners(miners)
{
}

TechDeveloper::~TechDeveloper() {

}

void TechDeveloper::Behavior() {
    while (true) {
        // Randomly select crypto miner which HW performance will be boosted
        if (!this->miners.empty()) {
            int miner_index = static_cast<int>(Uniform(0, this->miners.size()));
            this->miners.at(miner_index)->SetMiningPerformance(
                this->performance_boost
            );
        }

        // Repeat every 1-2 years
        Wait(Uniform(YEAR, 2 * YEAR));
    }
}
