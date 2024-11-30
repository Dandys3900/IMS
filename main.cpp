#include "entities/config_handler.h"

int main () {
    ConfigHandler* config_handler = new ConfigHandler();

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
    }

    Run();

    // Output simulation statistics
    SIMLIB_statistics.Output();

    // Cleanup
    delete config_handler;

    return EXIT_SUCCESS;
}
