#include "entities/config_handler.h"

int runExperiment(string filename) {
    ConfigHandler* config_handler = new ConfigHandler();

    try {
        // Load enitities from
        config_handler->InitSimulation(filename);
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

int main (int argc, char* argv[]) {
    // Globally set output precious to 3-decimal places
    cout << fixed << setprecision(3);
    RandomSeed(time(NULL));

    for (int i = 1; i < argc; i++) {
        runExperiment(string(argv[i]));
        cout << "+++++++++++++++++++++++++++++++ simulation done +++++++++++++++++++++++++++++++" << endl;
    }

    return EXIT_SUCCESS;
}
