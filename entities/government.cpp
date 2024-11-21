#include "crypto_exchange.h"
#include "government.h"

Government::Government(double init_taxes, vector<Exchange*> exchanges)
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

double Government::GetCurrentTaxes() {
    return this->init_taxes;
}

void Government::PrintStats() {
    cout << "-------------------------"                    << endl;
    cout << "Governments stats:"                           << endl;
    cout << " -> Current crypto tax: " << this->init_taxes << endl;
    cout << "-------------------------"                    << endl;
}
