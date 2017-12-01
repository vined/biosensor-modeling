#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>


#define OUTPUT "../out/"

void printVector(std::vector<double> vect, int max) {
    int i = 0;
    for (double val : vect) {
        if (max != 0 && i > max)
            return;
        std::cout << val << ",";
        i++;
   }
    std::cout << std::endl;
}

void exportVector(std::string name, std::vector<double> vect, int precision) {

    std::string fileName = OUTPUT + name + ".dat";

    std::cout << "Exporting " << fileName << "" << std::endl;

    std::ofstream dat;
    dat.open(fileName);
    dat.precision(precision);

    dat << "# " << name << std::endl;

    for (double val : vect) {
        dat << val << std::endl;
    }

    dat.close();
    std::cout << "Exporting " << fileName << " done." << std::endl;
}
