#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

#include "values-net.h"
#include "machine-precision.h"
#include "time-intervals.h"
#include "approximations-utils.h"
#include "output-utils.h"
#include "parameters-utils.h"
#include "approximations.h"


#define ARG_COUNT 1+5+10


static void show_usage() {
    std::cout
            << "Usage: biosensor-modeling de dm Nb T M\n"
            << "Demo mode: biosensor-modeling\n\n"

            << "Options:\n"
            << "\t-h \t\tShow this help message\n"

            << "Model parameters:\n"
            //Grid parameters
            << "\tde \t\tWidth of bio-sensor ferment part (micrometers)\n"
            << "\tdm \t\tWidth of bio-sensor membrane part (micrometers)\n"
            << "\tNb \t\tDensity of bio-sensor width values (int)\n"
            << "\tT \t\tMaximum model time (s)\n"
            << "\tM \t\tTime steps count (int)\n"
            //Model parameters
            << "\tDse \t\tSubstrate diffusion coefficient of ferment part (micrometers^2 / s)\n"
            << "\tDsm \t\tSubstrate diffusion coefficient of membrane part (micrometers^2 / s)\n"
            << "\tDpe \t\tProduct diffusion coefficient of ferment part (micrometers^2 / s)\n"
            << "\tDpm \t\tProduct diffusion coefficient of membrane part (micrometers^2 / s)\n"
            << "\tC1 \t\tDegradation of substrate coefficient (s^-1)\n"
            << "\tC2 \t\tDegradation of product coefficient (s^-1)\n"
            << "\tVmax \t\tMaximum reaction speed in ferment part (mmol/(m^3 s))\n"
            << "\tKm \t\tMichaelis constant (mol / m^3)\n"
            << "\tS0 \t\tInitial substrate concentration (mol / m^3)\n"
            << "\tne \t\tCount of electric current transfering electrons in electrode\n"

            << "Result is outputed into files:\n"
            << "\tx.txt \t\tBio-sensor length coordinates\n"
            << "\ty.txt \t\tTime field\n"
            << "\tS.txt \t\tSubstrate concentration over time (mol / m^3) [2D]\n"
            << "\tP.txt \t\tProduct concentration over time (mol / m^3) [2D]\n"
            << "\tI.txt \t\tCurrent near electrode over time (A / m^2)\n"
            << std::endl;
}

/*
    - Modeling -
i - electric current
n_e - electrons count (1 or 2)
F - Faraday's constant 96485.3365 C/mol
D_Pe - diffusion coefficient in ferment near electrode
*/
int main(int argc, char *argv[]) {

    // Retrieving parameters
    grid_parameters grid_params;
    model_parameters model_params;

    if (argc == 1) {
        std::cout << "-- Demo Mode --\n"
                  << "To see the manual run biosensor-modeling -h" << std::endl;
        grid_params = getDemoGridParameters();
        model_params = getDemoModelParameters();

    } else if (argc == ARG_COUNT) {
        grid_params = parseGridParameters(argc, argv);
        model_params = parseModelParameters(argc, argv);

    } else {
        show_usage();
        return 0;
    }

    std::cout << grid_params.toString() << std::endl;
    std::cout << model_params.toString() << std::endl;


    // Checking system information
    int mp = getMachinePrecision();
    std::cout.precision(mp);
    std::cout << "Machine precision: " << mp << std::endl;
    std::cout << "Size of double: " << sizeof(double) << std::endl;

    double delta = pow(10.0, -mp / 2);
    std::cout << "Delta: " << delta << std::endl;


    // Creating x and t values field
    std::cout << "Generating x values" << std::endl;
    values_net_params field_params = getNonLinearValuesNetParams(grid_params.d_e, grid_params.d_m, grid_params.N_b);
    std::cout << "q: " << field_params.q << std::endl;
    std::vector<double> x = generateNonLinearValuesNet(field_params);
    int n = x.size();
    std::cout << "Done, x values size: " << n << std::endl;
    exportVector("x", x, mp);

    std::cout << "Generating t values" << std::endl;
    std::vector<double> t = getTimeIntervals(grid_params.T, grid_params.M, -mp);
    std::cout << "Done, t values size: " << t.size() << std::endl;
    exportVector("t", t, mp);


    std::cout << "Generating f, g values" << std::endl;
    std::vector<double> f = getZeroVector(n);
    std::vector<double> g = f;

    std::cout << "Generating alpha, D_s, D_p values" << std::endl;
    std::pair<int, int> de_dm_lengths = get_de_dm_segments_lengths(field_params);
    std::vector<double> alpha = get_alpha(de_dm_lengths.first, de_dm_lengths.second);
    exportVector("alpha", alpha, mp);

    std::vector<double> D_s = get_D(alpha, model_params.Dse, model_params.Dsm);
    exportVector("D_s", D_s, mp);
    std::vector<double> D_p = get_D(alpha, model_params.Dpe, model_params.Dpm);
    exportVector("D_p", D_p, mp);


    std::cout << "Approximating I" << std::endl;
    I_approximation_result = approximate_I(
            x,
            t,
            D_s,
            D_p,
            alpha,
            f,
            g,
            model_params.S0,
            model_params.Vmax,
            model_params.Km,
            model_params.C1,
            model_params.C2,
            model_params.ne,
            field_params.q,
            delta
    );
    
    std::cout << "I approximation finished, exporting results..." << std::endl;

    return 0;
}

