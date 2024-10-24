#include "government.h"

Government::Government(Exchange** exchanges)
    : exchanges(exchanges)
{
}

Government::~Government() {

}

void Government::Behavior() {
    // Randomly select exchange to close (f.e. with 10% chance of closing)
}
