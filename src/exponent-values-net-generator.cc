#include <cmath>

#include "exponent-values-net-generator.h"

using namespace std;

/*
Todo: test the following conditions
h[0] <= (h[n-1])^2
h[0] << h[n-1] << 1
h[n-1]=h_max
sum(h)=1

q>1
h[0]=(q-1)/(q^n-1)


Example
N_b = 10 (h_max = 1/N_b )
N = 26, q = 1.10111174070019
*/

double _get_h_max(int N_b) {
    return 1.0 / N_b;
}

double _get_first_q_approx(double h_max) {
    return 1.0 + h_max;
}

int _get_N_approx(double q, double h_max) {
    return ceil( (log(1 + (q-1)/pow(h_max,2))) / log(q));
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

int _get_N(int N_b) {

    double h_max = _get_h_max(N_b);
    double q = _get_first_q_approx(h_max);
    int N = 0;
    int N_approx = _get_N_approx(q, h_max);

    while (N != N_approx) {
        N = N_approx;
        q = _get_next_q_approx(q, N_approx, h_max);
        N_approx = _get_N_approx(q, h_max);
    }

    return N;
}

double _get_next_h(double h_prev, double q) {
    return h_prev * q;
}

void generateExponentialNet(int N_b, double result[], int l) {
}


