#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include "crypto_exchange.h"
#include <simlib.h>

class Government : public Event {
    private:
        Exchange** exchanges;

    public:
        Government(Exchange** exchanges);
        ~Government();

        void Behavior() override;
};

#endif // GOVERNMENT_H
