#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

#include "s-approximations.h"
#include "approximations-utils.h"
#include "output-utils.h"


#define MAX_ITERATIONS 20

std::vector<double> _get_F(
        double t_step,
        double V_max,
        double K_m,
        std::vector<double> S_k,
        std::vector<double> y,
        std::vector<double> alpha,
        std::vector<double> f
) {
    std::vector<double> F;

    for (unsigned i = 1; i < y.size() - 1; i++) {
        F.push_back(
                (2 * S_k[i] / t_step) - ( (alpha[i] * V_max * y[i]) / (K_m + y[i]) ) + f[i]
        );
    }
    return F;
}

double _get_new_y_0(
        std::vector<double> A,
        std::vector<double> B,
        std::vector<double> Y,
        double S_0,
        double q
) {
    double l = pow(1 + q, 2);
    double a = l * (S_0 * B[1] + Y[1]) - (S_0 * B[2]) - Y[2];
    double b = l * (1 - A[1]) + A[2] - 1;

    return a/b;
}

std::vector<double> _get_new_approximations(
        std::vector<double> y_old,
        std::vector<double> A,
        std::vector<double> B,
        std::vector<double> Y,
        double q
) {
    std::vector<double> y_new;
    double S_0 = y_old[y_old.size()-1];

    double y0 = _get_new_y_0(A, B, Y, S_0, q);
    y_new.push_back(y0);

    for (int i = 1; i < y_old.size()-1; i++) {
        y_new.push_back(
                y0 * A[i] + S_0 * B[i] + Y[i]
        );
    }
    y_new.push_back(S_0);

    return y_new;
}

std::vector<double> getApproximateSkHalf(
        std::vector<double> S_k,
        std::vector<double> alpha,
        std::vector<double> f,

        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> A,
        std::vector<double> B,

        double t_step,
        double V_max,
        double K_m,
        double C1,
        double q,
        double delta
) {

    std::vector<double> y_old(S_k);
    std::vector<double> y_new;

    double progress = 0;
    double residual = 0;
    double allowed_error = 0;
    int i = 0;

    do {
        if (i > MAX_ITERATIONS) {
            throw 100;
        }
        i++;

        std::vector<double> F = _get_F(t_step, V_max, K_m, S_k, y_old, alpha, f);
        std::vector<double> Y = solveCustomisedTridiagonalThomasMatrix3(a, b, c, F, 0.0, 0.0);

        y_new = _get_new_approximations(y_old, A, B, Y, q);

        std::vector<double> F_new = _get_F(t_step, V_max, K_m, S_k, y_new, alpha, f);

        progress = getProgress(y_new, y_old);
        residual = getResidual(y_new, a, b, c, F_new);
        allowed_error = getAllowedError(y_new, delta);
        y_old = y_new;

    } while (allowed_error < progress || allowed_error < residual);

    return y_new;
}
