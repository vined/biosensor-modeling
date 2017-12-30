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
#include "file-utils.h"
#include "approximations.h"


#define ALL_ARG_COUNT 1+5+9

#define MANAGER_ID 0

int main(int argc, char *argv[]) {

    // OpenMPI setup

    int processors_count;
    int processor_id;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_id);
    MPI_Comm_size(MPI_COMM_WORLD, &processors_count);

    if (processor_id == MANAGER_ID) {
        std::cout << "Processors count: " << processors_count << std::endl;
    }


    // Modeling parameters

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

    int c_size;
    double *C1;
    double *C2;


    // Calculation results

    double *I;
    double *T;


    // Retrieving parameters

    if (argc == 3) {
        grid_params = getDemoGridParameters();
        model_params = getDemoModelParameters();

    } else {
        std::cout << "Invalid usage" << std::endl;
        std::cout << "Usage: biosensor-modeling c1-data-file c2-data-file" << std::endl;
        MPI_Finalize();
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


    // Read C size

    c_size = getFileLinesCount(argv[1]);

    MPI_Barrier(MPI_COMM_WORLD);

    C1 = (double *) malloc(c_size);
    C2 = (double *) malloc(c_size);
    I = (double *) malloc(c_size);
    T = (double *) malloc(c_size);


    // Read C values

    readDoublesFromFile(argv[1], C1);

    //MPI_Barrier(MPI_COMM_WORLD);

    readDoublesFromFile(argv[2], C2);

    MPI_Barrier(MPI_COMM_WORLD);
        for (unsigned i = 0; i < c_size; i++) {
            std::cout << processor_id << " C2 " << C2[i] << std::endl;
        }

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

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Gather(
            &I_t.first, 1, MPI_DOUBLE,
            I, 1, MPI_DOUBLE,
            MANAGER_ID, MPI_COMM_WORLD
    );

    MPI_Gather(
            &I_t.second, 1, MPI_DOUBLE,
            T, 1, MPI_DOUBLE,
            MANAGER_ID, MPI_COMM_WORLD
    );

    MPI_Barrier(MPI_COMM_WORLD);

    // Results

    if (processor_id == MANAGER_ID) {
        for (unsigned i; i < processors_count; i++) {
            std::cout << i << " I = " << I[i] << " A m^(-2), t* = " << T[i] << " s" << std::endl;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}

