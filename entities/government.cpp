#include "crypto_exchange.h"
#include "government.h"

Government::Government(double init_taxes, vector<Exchange*> exchanges)
    : init_taxes(init_taxes),
      exchanges(exchanges)
{
}

Government::~Government() {
    this->PrintStats();
}

void Government::Behavior() {
    while(true) {
        // It's 8% probability government will shutdown exchange
        if (Random() <= 0.08) {
            // Randomly select exchange to close
            int exchange_index = static_cast<int>(Uniform(0, this->exchanges.size()));

            this->exchanges.at(exchange_index)->ClosingExchange();
        }

        // Update taxes
        this->UpdateTaxes();

        // Repeat every half-year
        Wait(HALF_YEAR);
    }
}

void Government::UpdateTaxes() {
    // Update government taxes in range <-1.2% , +1.2%>
    this->init_taxes += Uniform(-0.012, 0.012);

    // Avoid negative taxes
    if (this->init_taxes < 0.0)
        this->init_taxes = 0.0;

    // Populate change to exchanges
    for (auto exchange : this->exchanges)
        exchange->UpdateGovTaxes(this->init_taxes);
}

double Government::GetCurrentTaxes() {
    return this->init_taxes;
}

void Government::PrintStats() {
    cout << "-------------------------"                    << endl;
    cout << "Governments stats:"                           << endl;
    cout << " -> Current crypto tax: " << (this->init_taxes * 100) << "%" << endl;
    cout << "-------------------------"                    << endl;
}
