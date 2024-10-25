#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include "crypto_exchange.h"
#include <simlib.h>

class Government : public Event {
    private:
        double init_taxes;
        Exchange** exchanges;

    public:
        Government(double init_taxes, Exchange** exchanges);
        ~Government();

        void Behavior() override;
        void UpdateTaxes(double new_value);
};

#endif // GOVERNMENT_H
