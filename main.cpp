#include "entities/config_handler.h"

int main (int argc, char *argv[]) {
    ConfigHandler* config_handler = new ConfigHandler();
    // Load enitities from
    config_handler->InitSimulation();

    Run();

    // Output simulation statistics
    SIMLIB_statistics.Output();
    // TODO: Ouptut enitites stats for each experiment

    // Cleanup
    delete config_handler;

    return EXIT_SUCCESS;
}
