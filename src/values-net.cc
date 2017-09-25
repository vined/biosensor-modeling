#include <cmath>

#include "exponent-intervals.h"
#include "values-range.h"
#include "values-net.h"

using namespace std;

double _get_next_h(double h_prev, double q) {
    return h_prev * q;
}

double generateNonLinearValuesNet(double d_e, double d_m, int N_b) {

    // Common values
    double h_max = get_h_max(d_e, d_m, N_b);
    double q = get_q(N_b, h_max);
    int N_i = get_N(q, h_max);
    int N = 4 * N_i;

    // I intervals construction
    double I_length = get_I_length(d_e, d_m);

    // Theta interval construction
    double theta_length = get_theta_length(d_e, d_m);

    if (theta_length) {

        int N_theta = get_N_theta(d_e, d_m, N_b);
        double h_I_max = get_h_I_max(I_length, h_max);

        N += N_theta;
    }

    // Todo: construct array
    // Todo: fill with values

    return 0.0;
}
