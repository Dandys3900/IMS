#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include "includes.h"

class Exchange;

class Government : public Process {
    private:
        double init_taxes;
        vector<Exchange*> exchanges;

    public:
        Government(double init_taxes, vector<Exchange*> exchanges);
        ~Government();

        void Behavior() override;
        void UpdateTaxes();
        double GetCurrentTaxes();
        void PrintStats();
};

#endif // GOVERNMENT_H
