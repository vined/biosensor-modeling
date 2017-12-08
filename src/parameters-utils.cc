#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "approximations-utils.h"
#include "parameters-utils.h"


parameters parseParameters(std::vector <std::string> argv) {
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
                    std::stof(argv[9]), //C1
                    std::stof(argv[10]), //C2
                    std::stof(argv[11]), //Vmax
                    std::stof(argv[12]), //Km
                    std::stof(argv[13]), //S0
                    std::stoi(argv[14]), //L
                    std::stoi(argv[15])  //ne
            );
}

std::ifstream openFile(std::string fileName) {
    std::ifstream file;
    file.open(fileName);

    if (file.is_open()) {
        return file;
    }

    std::cout << "Failed to open file: " << fileName << std::endl;
    throw 200;
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

parameters readParameters(std::string fileName) {

    std::ifstream paramsFile = openFile(fileName);
    std::string line;
    std::vector <std::string> params;

    while (getline(paramsFile, line)) {

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
