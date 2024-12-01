#include "entities/config_handler.h"

int main () {
    ConfigHandler* config_handler = new ConfigHandler();
    // Globally set output precious to 3-decimal places
    cout << fixed << setprecision(3);

    try {
        RandomSeed(time(NULL));
        // Load enitities from
        config_handler->InitSimulation();
        // Activate entities
        config_handler->ActivateSimulation();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    } catch (const char* e) {
        cout << "Error: " << e << endl;
        return EXIT_FAILURE;
    } catch (...) {
        cout << "Error during simulation init, make sure config file has correct format" << endl;
        return EXIT_FAILURE;
    }

    Run();

    // Cleanup
    delete config_handler;

    return EXIT_SUCCESS;
}
