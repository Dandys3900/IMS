#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include "includes.h"

class Government : public Event {
    private:
        Exchange** exchanges;

    public:
        Government(Exchange** exchanges);
        ~Government();

        void Behavior() override;
};

#endif // GOVERNMENT_H
