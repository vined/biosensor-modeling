#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <ctime>

#include "values-net.h"
#include "machine-precision.h"
#include "time-intervals.h"
#include "approximations-utils.h"
#include "output-utils.h"
#include "parameters-utils.h"
#include "approximations.h"


#define ARG_COUNT 1+5+10


static void show_usage() {
    std::cout << "Usage: biosensor-modeling [parameter-file-name]" << std::endl;
}

int main(int argc, char *argv[]) {

    // Retrieving parameters

    if (argc != 2) {
        show_usage();
        return 0;
    }

    parameters params = readParameters(argv[1]);
    std::cout << params.toString() << std::endl;


    // Checking system information

    int mp = getMachinePrecision();
    std::cout.precision(mp);
    std::cout << "Machine precision: " << mp << std::endl;
    std::cout << "Size of double: " << sizeof(double) << std::endl;

    double delta = pow(10.0, -mp / 2);
    std::cout << "Delta: " << delta << std::endl;


    // Creating x and t values field

    std::cout << "Generating x values" << std::endl;
    values_net_params field_params = getNonLinearValuesNetParams(params.d_e, params.d_m, params.N_b);
    std::cout << "q: " << field_params.q << std::endl;

    std::vector<double> x = generateNonLinearValuesNet(field_params);
    int n = x.size();
    std::cout << "Done, x values size: " << n << std::endl;

    std::cout << "Generating t values" << std::endl;
    std::vector<double> t = getTimeIntervals(params.T, params.M, -mp);
    std::cout << "Done, t values size: " << t.size() << std::endl;


    // Other model parameters

    std::cout << "Generating f, g values" << std::endl;
    std::vector<double> f = getZeroVector(n);
    std::vector<double> g = f;

    std::cout << "Generating alpha, D_s, D_p values" << std::endl;
    std::pair<int, int> de_dm_lengths = get_de_dm_segments_lengths(field_params);
    std::vector<double> alpha = get_alpha(de_dm_lengths.first, de_dm_lengths.second);

    std::vector<double> D_s = get_D(alpha, params.Dse, params.Dsm);
    std::vector<double> D_p = get_D(alpha, params.Dpe, params.Dpm);


    // Approximation

    std::cout << "Approximating I..." << std::endl;
    time_t t1 = time(NULL);

    std::vector<double> I = approximate_I(
            x,
            t,
            D_s,
            D_p,
            alpha,
            f,
            g,
            params.S0,
            params.Vmax,
            params.Km,
            params.C1,
            params.C2,
            params.ne,
            field_params.q,
            delta
    );

    std::cout << "I approximation finished in " << difftime(time(NULL), t1) << "s, exporting results..." << std::endl;
    std::cout << "I size: " << I.size() << std::endl;


    // Results

    // Todo: Calculate i

    exportMultiVector("I", {"t", "I"}, {t, I}, mp);

    return 0;
}

