#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "values-net.h"
#include "machine-precision.h"
#include "time-intervals.h"
#include "output-utils.h"


#define ARG_COUNT 6


static void show_usage()
{
    std::cout << "Usage: biosensor-modeling de dm Nb T M\n"
              << "Demo mode: biosensor-modeling\n\n"
              << "Options:\n"
              << "\t-h\t\tShow this help message\n"
              << "Parameters:\n"
              << "\tde\t\tWidth of bio-sensor ferment part\n"
              << "\tdm\t\tWidth of bio-sensor membrane part\n"
              << "\tNb\t\tDensity of bio-sensor width values (x)\n"
              << "\tT\t\tMaximum model time\n"
              << "\tM\t\tTime steps count\n"
              << std::endl;
}

struct parameters {
    // Width of bio-sensor parts widths
    double d_e;
    double d_m;
    // Width and time matrix parameters
    int N_b;
    int T;
    int M;

    parameters() {}
    parameters(double _d_e, double _d_m, int _N_b, int _T, int _M) {
        d_e = _d_e;
        d_m = _d_m;
        N_b = _N_b;
        T = _T;
        M = _M;
    }

    std::string toString() {
        std::string str = "Parameters: ";
        str += "d_e=" + std::to_string(d_e) + ", "
            + "d_m=" + std::to_string(d_m) + ", "
            + "N_b=" + std::to_string(N_b) + ", "
            + "T=" + std::to_string(T) + ", "
            + "M=" + std::to_string(M);

        return str;
    }
};

static parameters getDemoModeParameters() {
    return parameters
    (
        4.0, // d_e
        5.0, // d_m
        1000, // N_b
        1000, // T
        1000000 // M
    );
}

static parameters parseParameters(int argc, char* argv[]) {
    return parameters
    (
        atof(argv[1]), // d_e
        atof(argv[2]), // d_m
        atoi(argv[3]), // N_b
        atoi(argv[4]), // T
        atoi(argv[5])  // M
    );
}

void modeling(std::vector<double> x, std::vector<double> t, double delta);

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
    parameters params;

    if (argc == 1) {
        std::cout << "-- Demo Mode --\n"
                  << "To see the manual run biosensor-modeling -h" << std::endl;
        params = getDemoModeParameters();

    } else if (argc == ARG_COUNT) {
        params = parseParameters(argc, argv);
    } else {
        show_usage();
        return 0;
    }

    std::cout << params.toString() << std::endl;

    // Generic system information
    int mp = getMachinePrecision();
    std::cout.precision(mp-1);
    std::cout << "Machine precision : " << mp << std::endl;
    std::cout << "Size of double : " << sizeof(double) << std::endl;

    double delta = 10^(mp/2);

    // Creating x and t values net
    std::cout << "Generating x values" << std::endl;
    std::vector<double> x = generateNonLinearValuesNet(params.d_e, params.d_m, params.N_b);
    std::cout << "Done, x values size: " << x.size() << std::endl;
    exportVector("x", x);

    std::cout << "Generating t values" << std::endl;
    std::vector<double> t = getTimeIntervals(params.T, params.M, mp);
    std::cout << "Done, t values size: " << t.size() << std::endl;
    exportVector("t", t);

    return 0;
}

/*
Next - implement 5.6.4 and 5.6.5
*/

