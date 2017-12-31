#include <stdlib.h>
#include <vector>

#include "approximations-utils.h"
#include "parameters-utils.h"

#define C_START 15


std::vector<double> parseC(std::vector <std::string> argv, unsigned from, unsigned to) {
    std::vector<double> C;

    for (unsigned i = from; i < to; i++) {
        C.push_back(std::stof(argv[i]));
    }

    return C;
}

parameters parseParameters(std::vector <std::string> argv) {
    unsigned C_size = std::stoi(argv[14]);

    std::vector<double> C1 = parseC(argv, C_START, C_START + C_size);
    std::vector<double> C2 = parseC(argv, C_START + C_size, C_START + C_size * 2);

    return parameters
            (
                    //Grid parameters
                    std::stof(argv[0]), // d_e
                    std::stof(argv[1]), // d_m
                    std::stoi(argv[2]), // N_b
                    std::stoi(argv[3]), // T
                    std::stoi(argv[4]),  // M
                    //Model parameters
                    std::stof(argv[5]), //Dse
                    std::stof(argv[6]), //Dsm
                    std::stof(argv[7]), //Dpe
                    std::stof(argv[8]), //Dpm
                    std::stof(argv[9]), //Vmax
                    std::stof(argv[10]), //Km
                    std::stof(argv[11]), //S0
                    std::stoi(argv[12]), //L
                    std::stoi(argv[13]), //ne
                    C_size,
                    C1,
                    C2
            );
}

bool isCommentOrEmpty(std::string line) {
    return line.size() == 0 || line[0] == '#';
}

std::string getValue(std::string line) {

    std::size_t pos = line.find_first_of(" #;,\t\n");

    if (pos != std::string::npos) {
        return line.substr(0, pos);
    }
    return line;
}

parameters readParameters(std::vector <std::string> lines) {

    std::vector <std::string> params;

    for (std::string line: lines) {

        if (!isCommentOrEmpty(line)) {
            params.push_back(
                    getValue(line)
            );
        }
    }

    return parseParameters(params);
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
