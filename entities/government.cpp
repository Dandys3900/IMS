#include "government.h"

Government::Government(double init_taxes, unordered_set<Exchange*> exchanges)
    : init_taxes(init_taxes),
      exchanges(exchanges)
{
}

Government::~Government() {

}

void Government::Behavior() {
    // Randomly select exchange to close (f.e. with 10% chance of closing)
}

void Government::UpdateTaxes(double new_value) {
    // F.e. decide by current crypto price whether its good idea to set new taxes to all exchanges
    // Use Exchange::UpdateGovTaxes()
}
