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
    parameters params;
    values_net_params field_params;
    std::vector<double> x;
    std::vector<double> t;
    std::vector<double> f;
    std::vector<double> g;
    std::vector<double> alpha;
    std::vector<double> D_s;
    std::vector<double> D_p;


    // Read parameters

    if (argc != 2 && processor_id == MANAGER_ID) {
        std::cout << "Invalid usage" << std::endl;
        std::cout << "Usage: biosensor-modeling parameters-file" << std::endl;
        std::cout << "Check example in params.data" << std::endl;
        MPI_Finalize();
        return 0;
    }

    std::vector <std::string> unparsed_params = readFileLines(argv[1]);
    params = readParameters(unparsed_params);

    if (processor_id == MANAGER_ID) {
        std::cout << params.toString() << std::endl;
        for (unsigned i = 0; i < params.C_count; i++) {
            std::cout << "C1 " << params.C1[i] << " \tC2 " << params.C2[i] << std::endl;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);


    // Gathering system info

    mp = getMachinePrecision();
    delta = pow(10.0, -mp / 2);


    // Creating model mesh

    field_params = getNonLinearValuesNetParams(params.d_e, params.d_m, params.N_b);

    x = generateNonLinearValuesNet(field_params);
    t = getTimeIntervals(params.T, params.M, -mp);


    // Other model parameters

    f = getZeroVector(x.size());
    g = f;

    std::pair<int, int> de_dm_lengths = get_de_dm_segments_lengths(field_params);
    alpha = get_alpha(de_dm_lengths.first, de_dm_lengths.second);

    D_s = get_D(alpha, params.Dse, params.Dsm);
    D_p = get_D(alpha, params.Dpe, params.Dpm);

    MPI_Barrier(MPI_COMM_WORLD);


    // Splitting the load

    int *counts = (int *) malloc(processors_count);
    int *displs = (int *) malloc(processors_count);

    if (processor_id == MANAGER_ID) {

        int size = params.C_count / processors_count;
        int tail = params.C_count % processors_count;

        for (unsigned i = 0; i < processors_count; i++) {

            int cnt = size;
            if (i < tail) cnt++;

            counts[i] = cnt;

            if (i == 0) {
                displs[i] = 0;
            } else {
                displs[i] = displs[i - 1] + counts[i - 1];
            }
        }
    }

    int c_length;
    MPI_Scatter(
            counts, 1, MPI_INT,
            &c_length, 1, MPI_INT,
            MANAGER_ID, MPI_COMM_WORLD
    );
    std::cout << processor_id << " c_length " << c_length << std::endl;

    double *C1 = (double *) malloc(c_length);
    double *C2 = (double *) malloc(c_length);

    MPI_Scatterv(
            &params.C1[0], counts, displs, MPI_DOUBLE,
            C1, c_length, MPI_DOUBLE,
            MANAGER_ID, MPI_COMM_WORLD
    );

    MPI_Scatterv(
            &params.C2[0], counts, displs, MPI_DOUBLE,
            C2, c_length, MPI_DOUBLE,
            MANAGER_ID, MPI_COMM_WORLD
    );


    // Approximation

    MPI_Barrier(MPI_COMM_WORLD);

    double *proc_I = (double *) malloc(c_length);
    double *proc_T = (double *) malloc(c_length);

    std::cout << processor_id << " Approximating..." << std::endl;
    for (unsigned i = 0; i < c_length; i++) {

        time_t t1 = time(NULL);
        std::cout << processor_id << " Approximating I with C1=" << C1[i] << " and C2=" << C2[i] << "..." << std::endl;

        std::pair<double, double> I_t = approximate_I(
                x,
                t,
                D_s,
                D_p,
                alpha,
                f,
                g,
                params,
                C1[i],
                C2[i],
                field_params.q,
                delta
        );

        proc_I[i] = I_t.first;
        proc_T[i] = I_t.second;
        std::cout << processor_id << " I approximation finished in " << difftime(time(NULL), t1) << "s" << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);


    // Calculation results

    double *I = (double *) malloc(params.C_count);
    double *T = (double *) malloc(params.C_count);

    MPI_Gatherv(
            &proc_I, c_length, MPI_DOUBLE,
            I, counts, displs, MPI_DOUBLE,
            MANAGER_ID, MPI_COMM_WORLD
    );

    MPI_Gatherv(
            &proc_T, c_length, MPI_DOUBLE,
            T, counts, displs, MPI_DOUBLE,
            MANAGER_ID, MPI_COMM_WORLD
    );

    MPI_Barrier(MPI_COMM_WORLD);


    // Printing results

    if (processor_id == MANAGER_ID) {
        for (unsigned i; i < params.C_count; i++) {
            std::cout << i << " I = " << I[i] << " A m^(-2), t* = " << T[i] << " s";
            std::cout << i << " (C1 = " << params.C1[i] << " (s^-1), C2 = " << params.C2[i] << " (s^-1))";
            std::cout << std::endl;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}

