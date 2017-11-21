#include <fstream>
#include <stdlib.h>


#include "parameters-utils.h"

// DEMO parameters
grid_parameters getDemoGridParameters() {
    return grid_parameters
            (
                    //Grid parameters
                    0.000004, // d_e
                    0.000005, // d_m
                    1000, // N_b
                    1000, // T
                    1000000 // M
            );
}

model_parameters getDemoModelParameters() {
//    char argv[][] = {
//            //Model parameters
//            "22", //Dse
//            "7", //Dsm
//            "20", //Dpe
//            "6", //Dpm
//            "0", //C1
//            "0", //C2
//            "0.3", //Vmax
//            "0.23", //Km
//            "0.07", //S0
//            "1" //ne
//    };
//    return parseModelParameters(0, argv);
    return model_parameters
            (
                    //Model parameters
                    22.0, //Dse
                    7.0, //Dsm
                    20.0, //Dpe
                    6.0, //Dpm
                    0.0, //C1
                    0.0, //C2
                    0.3, //Vmax
                    0.23, //Km
                    0.07, //S0
                    1 //ne
            );
}


// Parameters parsers
grid_parameters parseGridParameters(int argc, char *argv[]) {
    return grid_parameters
            (
                    //Grid parameters
                    atof(argv[1]), // d_e
                    atof(argv[2]), // d_m
                    atoi(argv[3]), // N_b
                    atoi(argv[4]), // T
                    atoi(argv[5])  // M
            );
}

model_parameters parseModelParameters(int argc, char *argv[]) {
    return model_parameters
            (
                    //Model parameters
                    atof(argv[6]), //Dse
                    atof(argv[7]), //Dsm
                    atof(argv[8]), //Dpe
                    atof(argv[9]), //Dpm
                    atof(argv[10]), //C1
                    atof(argv[11]), //C2
                    atof(argv[12]), //Vmax Todo convert
                    atof(argv[13]), //Km Todo convert
                    atof(argv[14]), //S0 Todo convert
                    atoi(argv[15])  //ne
            );
}
