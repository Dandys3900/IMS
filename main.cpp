#include "entities/config_handler.h"

int main (int argc, char *argv[]) {
    ConfigHandler* config_handler = new ConfigHandler();
    try {
        // Load enitities from
        config_handler->InitSimulation();
        // Activate entities
        config_handler->ActivateSimulation();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    Run();

    // Output simulation statistics
    SIMLIB_statistics.Output();
    // TODO: Ouptut enitites stats for each experiment

    // Cleanup
    //delete config_handler;

    return EXIT_SUCCESS;
}
