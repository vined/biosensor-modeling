#include <cmath>

#include "values-range.h"

using namespace std;


double get_I_length(double d_e, double d_m) {
    return fmin(d_e, d_m) / 2.0;
}

double get_h_I_max(double I_length, double h_max) {
    return I_length * h_max;
}

double get_theta_length(double d_e, double d_m) {
    return abs(d_e - d_m);
}

double get_theta_I_half_count(double d_e, double d_m) {
    return get_theta_length(d_e, d_m) / fmin(d_e, d_m);
}

int get_N_theta(double d_e, double d_m, int N_b) {
    return ceil( 2 * N_b * get_theta_I_half_count(d_e, d_m) );
}

double get_h_max(double d_e, double d_m, int N_b) {

    double N_theta = get_N_theta(d_e, d_m, N_b);

    if (N_theta == 0) {
        return 1.0 / N_b;
    } else {
        return (2.0 / N_theta) * get_theta_I_half_count(d_e, d_m);
    }
}
