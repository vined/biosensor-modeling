#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "p-approximations.h"
#include "approximations-utils.h"


#define MAX_ITERATIONS 1000


std::vector<double> _get_G(
        double t_step,
        double V_max,
        double K_m,
        std::vector<double> P_k,
        std::vector<double> S_k_half,
        std::vector<double> alpha,
        std::vector<double> g
) {
    std::vector<double> G;

    for (int i = 1; i < P_k.size() - 1; i++) {
        G.push_back(
                (2 * P_k[i] / t_step) + ((alpha[i] * V_max * S_k_half[i]) / (K_m + S_k_half[i])) + g[i]
        );
    }

    return G;
}

double _get_P_n(
        std::vector<double> B,
        std::vector<double> Y,
        double q
) {
    int N = B.size() - 1;

    double l = pow(1 + q, 2);
    double a = l * Y[N - 1] + Y[N - 2];
    double b = l * (1 - B[N - 1]) + B[N - 2] - 1;

    std::cout << "P_n: " << a/b << " Y[N-1]: " << Y[N-1] << " Y[N-2]: " << Y[N-2] << std::endl;
    return a / b;
}

std::vector<double> _get_new_approximations(
        std::vector<double> P_k,
        std::vector<double> B,
        std::vector<double> Y,
        double q
) {

    std::vector<double> P_k_half;
    double P_n = 0;//_get_P_n(B, Y, q);

    P_k_half.push_back(0.0);

    for (int i = 1; i < P_k.size() - 1; i++) {
        P_k_half.push_back(
                P_n * B[i] + Y[i]
        );
    }

    P_k_half.push_back(P_n);

    return P_k_half;
}

std::vector<double> getApproximatePkHalf(
        std::vector<double> P_k,
        std::vector<double> S_k_half,
        std::vector<double> alpha,
        std::vector<double> g,

        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> B,

        double t_step,
        double V_max,
        double K_m,
        double C2,
        double q
) {
    std::vector<double> G = _get_G(t_step, V_max, K_m, P_k, S_k_half, alpha, g);
    std::vector<double> Y = solveTridiagonalThomasMatrix(a, b, c, G, 0.0, 0.0);

    return _get_new_approximations(P_k, B, Y, q);
}
