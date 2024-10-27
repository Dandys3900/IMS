#include "tech_devs.h"

TechDeveloper::TechDeveloper(double efficiency_boost, unordered_set<CryptoMiner*> miners)
    : efficiency_boost(efficiency_boost),
      miners(miners)
{
}

TechDeveloper::~TechDeveloper() {

}

void TechDeveloper::Behavior() {
    // Randomly select crypto miner which efficiency will be boosted
    // use CryptoMiner::SetMiningEfficiency()
}
