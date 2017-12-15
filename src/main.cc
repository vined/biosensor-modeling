#include "mpi.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <ctime>

#include "values-net.h"
#include "machine-precision.h"
#include "time-intervals.h"
#include "approximations-utils.h"
#include "parameters-utils.h"
#include "approximations.h"


#define ALL_ARG_COUNT 1+5+9
#define NODES 3

#define OPEN_MPI_MANAGER_ID 0

int main(int argc, char *argv[]) {

    // OpenMPI setup

    int processors_count;
    int processor_id;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_id);
    MPI_Comm_size(MPI_COMM_WORLD, &processors_count);
    MPI_Barrier(MPI_COMM_WORLD);

    std::cout << "Processors count: " << processors_count << std::endl;
    std::cout << "Processor id: " << processor_id << std::endl;


    // Calculation parameters
    int mp;
    double delta;
    grid_parameters grid_params;
    model_parameters model_params;
    values_net_params field_params;
    std::vector<double> x;
    std::vector<double> t;
    std::vector<double> f;
    std::vector<double> g;
    std::vector<double> alpha;
    std::vector<double> D_s;
    std::vector<double> D_p;
    double C1[NODES] = {0.02, 0.025, 0.03};
    double C2[NODES] = {0.005, 0.01, 0.019};

    // Calculation results
    double I[NODES];
    double T[NODES];


    // Retrieving parameters
    std::cout << processor_id << " Arguments count" << argc << std::endl;
    if (argc == 1) {
        grid_params = getDemoGridParameters();
        model_params = getDemoModelParameters();

    } else if (argc == ALL_ARG_COUNT) {
        grid_params = parseGridParameters(argc, argv);
        model_params = parseModelParameters(argc, argv);

    } else {
        std::cout << "Invalid usage" << std::endl;
        return 0;
    }

    // Gathering system info
    mp = getMachinePrecision();
    delta = pow(10.0, -mp / 2);


    // Creating x and t values field
    field_params = getNonLinearValuesNetParams(grid_params.d_e, grid_params.d_m, grid_params.N_b);

    x = generateNonLinearValuesNet(field_params);
    t = getTimeIntervals(grid_params.T, grid_params.M, -mp);

    // Other model parameters

    f = getZeroVector(x.size());
    g = f;

    std::pair<int, int> de_dm_lengths = get_de_dm_segments_lengths(field_params);
    alpha = get_alpha(de_dm_lengths.first, de_dm_lengths.second);

    D_s = get_D(alpha, model_params.Dse, model_params.Dsm);
    D_p = get_D(alpha, model_params.Dpe, model_params.Dpm);

    MPI_Barrier(MPI_COMM_WORLD);


    // Approximation

    std::cout << processor_id << " Approximating I..." << std::endl;
    time_t t1 = time(NULL);

    std::pair<double, double> I_t = approximate_I(
            x,
            t,
            D_s,
            D_p,
            alpha,
            f,
            g,
            grid_params,
            model_params,
            C1[processor_id],
            C2[processor_id],
            field_params.q,
            delta
    );


    std::cout << processor_id << " I approximation finished in " << difftime(time(NULL), t1) << "s" << std::endl;

    MPI_Gather(
            &I_t.first, 1, MPI_DOUBLE,
            I, 1, MPI_DOUBLE,
            OPEN_MPI_MANAGER_ID, MPI_COMM_WORLD
    );

    MPI_Gather(
            &I_t.second, 1, MPI_DOUBLE,
            T, 1, MPI_DOUBLE,
            OPEN_MPI_MANAGER_ID, MPI_COMM_WORLD
    );

    MPI_Barrier( MPI_COMM_WORLD );

    // Results

    if (processor_id == OPEN_MPI_MANAGER_ID) {
        for (unsigned i; i < NODES; i++) {
            std::cout << i << " I = " << I[i] << " A m^(-2), t* = " << T[i] << " s" << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}

