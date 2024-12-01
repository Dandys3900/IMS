#include "entities/config_handler.h"

int runExperiment(string filename) {
    ConfigHandler* config_handler = new ConfigHandler();

    try {
        // Load enitities from
        if (!config_handler->InitSimulation(filename)) {
            cerr << "Error during simulation init, make sure config file has correct format" << endl;
            return EXIT_FAILURE;
        }
        // Activate entities
        config_handler->ActivateSimulation();

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    } catch (const char* e) {
        cerr << "Error: " << e << endl;
        return EXIT_FAILURE;
    } catch (...) {
        cerr << "Error during simulation init, make sure config file has correct format" << endl;
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
        int experiment_result = runExperiment(string(argv[i]));
        if (experiment_result != EXIT_SUCCESS) {
            return experiment_result;
        }
    }

    return EXIT_SUCCESS;
}
