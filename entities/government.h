#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include "includes.h"

class Exchange;

class Government : public Event {
    private:
        double init_taxes;
        unordered_set<Exchange*> exchanges;

    public:
        Government(double init_taxes, unordered_set<Exchange*> exchanges);
        ~Government();

        void Behavior() override;
        void UpdateTaxes(double new_value);
        double GetCurrentTaxes();
        void PrintStats();
};

#endif // GOVERNMENT_H
