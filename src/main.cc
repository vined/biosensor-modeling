#include <iostream>
#include <vector>

#include "values-net.h"
#include "machine-precision.h"
#include "time-intervals.h"
#include "output-utils.h"
#include "approximations-utils.h"
#include "parameters-utils.h"


#define ARG_COUNT 6


static void show_usage()
{
    std::cout << "Usage: biosensor-modeling de dm Nb T M\n"
              << "Demo mode: biosensor-modeling\n\n"

              << "Options:\n"
              << "\t-h\t\tShow this help message\n"

              << "Grid parameters:\n"
              << "\tde\t\tWidth of bio-sensor ferment part\n"
              << "\tdm\t\tWidth of bio-sensor membrane part\n"
              << "\tNb\t\tDensity of bio-sensor width values (x)\n"
              << "\tT\t\tMaximum model time\n"
              << "\tM\t\tTime steps count\n"
              << std::endl;
}

/*
    - Modeling -
i - electric current
n_e - electrons count (1 or 2)
F - Faraday's constant 96485.3365 C/mol
D_Pe - difussion coefficient in ferment near electrode

main formula from 5.4.2:
i(t_k) = n_e * F * D_Pe * ( - p0 + p1 - p2 )

p0 = ( (x[1]-x[2]) / (x[1]*x[2]) ) * P[k][0]
p2 = ( x[2] / (x[1] * (x[2]-x[1])) ) * P[k][1]
p = ( x[1] / (x[2] * (x[2]-x[1])) ) * P[k][2]
*/
int main(int argc, char* argv[]) {

    // Retrieving parameters
    grid_parameters grid_params;

    if (argc == 1) {
        std::cout << "-- Demo Mode --\n"
                  << "To see the manual run biosensor-modeling -h" << std::endl;
        grid_params = getDemoModeGridParameters();

    } else if (argc == ARG_COUNT) {
        grid_params = parseGridParameters(argc, argv);
    } else {
        show_usage();
        return 0;
    }

    std::cout << grid_params.toString() << std::endl;

    // Generic system information
    int mp = getMachinePrecision();
    std::cout.precision(mp-1);
    std::cout << "Machine precision: " << mp << std::endl;
    std::cout << "Size of double: " << sizeof(double) << std::endl;

    double delta = 10^(mp/2);
    std::cout << "Delta: " << delta << std::endl;

    // Creating x and t values net
    std::cout << "Generating x values" << std::endl;
    std::vector<double> x = generateNonLinearValuesNet(grid_params.d_e, grid_params.d_m, grid_params.N_b);
    std::cout << "Done, x values size: " << x.size() << std::endl;
    exportVector("x", x);

    std::cout << "Generating t values" << std::endl;
    std::vector<double> t = getTimeIntervals(grid_params.T, grid_params.M, mp);
    std::cout << "Done, t values size: " << t.size() << std::endl;
    exportVector("t", t);

    std::vector<double> dl {1, 1, 1, 1, 5};
    std::vector<double> d  {2, 2, 2, 2, 2};
    std::vector<double> du {5, 1, 1, 1, 1};
    std::vector<double> b  {1, 2, 3, 4, 5};
    std::vector<double> actual = solveTridiagonalMatrix(dl, d, du, b);
    printVector(actual, 1000);

    return 0;
}

