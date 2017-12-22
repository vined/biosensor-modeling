#include <fstream>
#include <stdlib.h>
#include <vector>


#include "approximations-utils.h"
#include "parameters-utils.h"

// DEMO parameters
grid_parameters getDemoGridParameters() {
    return grid_parameters
            (
                    //Grid parameters
                    9, // d_e
                    10, // d_m
                    50, // N_b
                    30, // T
                    10000 // M
            );
}

model_parameters getDemoModelParameters() {
    return model_parameters
            (
                    //Model parameters
                    22.0, //Dse
                    7.0, //Dsm
                    20.0, //Dpe
                    6.0, //Dpm
                    0.3, //Vmax
                    0.23, //Km
                    0.07, //S0
                    100, //L
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
                    atof(argv[10]), //Vmax
                    atof(argv[11]), //Km
                    atof(argv[12]), //S0
                    atof(argv[13]), //S0
                    atoi(argv[14])  //ne
            );
}

std::vector<double> get_alpha(int de_length, int dm_length) {

    std::vector<double> result = getVectorWithValue(de_length, 1.0);
    std::vector<double> de = getVectorWithValue(dm_length, 0.0);

    result.insert(result.end(), de.begin(), de.end());
    return result;
}

std::vector<double> get_D(std::vector<double> alpha, double D_e, double D_m) {

    std::vector<double> D;

    for (double a: alpha) {
        if (a > 0.0) {
            D.push_back(D_e);
        } else {
            D.push_back(D_m);
        }
    }

    return D;
}

int getLinesCount(char *buf, int size) {

    unsigned count = 0;
    for (unsigned i = 0; i < size; i++) {
        if (buf[i] == '\n') {
            count++;
        }
    }

    return count;
}

void readDoubles(char *buf, int size, double *out) {

    int j = 0;
    std::string d_str = "";

    for (unsigned i = 0; i < size; i++) {
        char c = buf[i];
        if (c == '\n') {
            out[j] = std::stod(d_str);
            d_str = "";
            j++;
        } else {
            d_str.append(1, c);
        }
    }
}
