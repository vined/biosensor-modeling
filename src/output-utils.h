#include <vector>

void printVector(std::vector<double> vect, int max);

void exportVector(std::string name, std::vector<double> vect, int precision);

void exportMultiVector(
        std::string name,
        std::vector <std::string> colNames,
        std::vector <std::vector<double>> vectors,
        int precision
);
