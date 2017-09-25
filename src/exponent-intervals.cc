#include <cmath>

#include "exponent-intervals.h"

using namespace std;

#define MAX_N_ITERATIONS 20

// Private
double _get_first_q_approx(double h_max) {
    return 1.0 + h_max;
}

double _get_q_error(double q, int N, double h_max) {
    return (pow(q,(N-1)) * ((q-1)/(pow(q,N)-1))) - h_max;
}

double _get_q_derivative_error(double q, int N) {
    return (pow(q,(2*N-2)) - N*pow(q,(N-1)) + N*pow(q,(N-2)) - pow(q,(N-2))) / pow((pow(q,N) - 1.0),2);
}

double _get_next_q_approx(double q, int N, double h_max) {
    return q - (_get_q_error(q, N, h_max) / _get_q_derivative_error(q, N));
}

// Public
double get_user_h_max(int N_b) {
    return 1.0 / N_b;
}

int get_N(double q, double h_max) {
    return ceil( (log(1 + (q-1)/pow(h_max,2))) / log(q));
}

double get_q(int N_b, double h_max) {

    double q = _get_first_q_approx(h_max);
    int N = 0, i = 0;
    int N_approx = get_N(q, h_max);

    while (N != N_approx) {

        if (i > MAX_N_ITERATIONS) {
            // Too many iterations
            throw 10;
        }

        N = N_approx;
        q = _get_next_q_approx(q, N_approx, h_max);
        N_approx = get_N(q, h_max);
        i++;
    }

    return q;
}
