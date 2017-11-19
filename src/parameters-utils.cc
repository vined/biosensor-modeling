#include <fstream>
#include <stdlib.h>


#include "parameters-utils.h"

grid_parameters getDemoModeGridParameters() {
    return grid_parameters
            (
                    4.0, // d_e
                    5.0, // d_m
                    1000, // N_b
                    1000, // T
                    1000000 // M
            );
}

grid_parameters parseGridParameters(int argc, char *argv[]) {
    return grid_parameters
            (
                    atof(argv[1]), // d_e
                    atof(argv[2]), // d_m
                    atoi(argv[3]), // N_b
                    atoi(argv[4]), // T
                    atoi(argv[5])  // M
            );
}

