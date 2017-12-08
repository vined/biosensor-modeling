#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "approximations-utils.h"
#include "s-approximations.h"
#include "p-approximations.h"
#include "approximations.h"
#include "output-utils.h"


#define F 96485.3365 // Faraday constant (C/mol)

std::vector<double> approximate_I(
        std::vector<double> x,
        std::vector<double> t,
        std::vector<double> D_s,
        std::vector<double> D_p,
        std::vector<double> alpha,
        std::vector<double> f,
        std::vector<double> g,
        double S_0,
        double V_max,
        double K_m,
        double C1,
        double C2,
        int n_e,
        double q,
        double delta
) {
    double p0 = (x[1] + x[2]) / (x[1] * x[2]);
    double p1 = x[2] / (x[1] * (x[2] - x[1]));
    double p2 = x[1] / (x[2] * (x[2] - x[1]));

    std::vector<double> I;
    I.push_back(0.0);

    // S initial values
    // Todo generate exponential Sk from S0
    std::vector<double> S_k = getZeroVector(x.size() - 1);
    S_k.push_back(S_0);
    exportMultiVector("Sk0", {"x", "S"}, {x, S_k}, 15);

    // P initial values
    std::vector<double> P_k = getZeroVector(x.size());

    // To optimize calculations, a, b, c for S and P will be recalculated only when t_step is changing
    double t_step = 0;

    std::vector<double> s_a = get_a(D_s, x);
    std::vector<double> s_b = get_b(D_s, x);
    std::vector<double> s_c;
    std::vector<double> s_A;
    std::vector<double> s_B;

    std::vector<double> p_a = get_a(D_p, x);
    std::vector<double> p_b = get_b(D_p, x);
    std::vector<double> p_c;
    std::vector<double> p_B;

    std::vector<double> zero_v = getZeroVector(x.size() - 2);

    for (int i = 1; i < t.size() - 1; i++) {

        double new_t_step = t[i + 1] - t[i];
        if (new_t_step > t_step) {
            t_step = new_t_step;

            s_c = get_c(t_step, C1, s_a, s_b);
            s_A = solveTridiagonalThomasMatrix(s_a, s_b, s_c, zero_v, 1.0, 0.0);
            s_B = solveTridiagonalThomasMatrix(s_a, s_b, s_c, zero_v, 0.0, 1.0);

            p_c = get_c(t_step, C2, p_a, p_b);
            p_B = solveTridiagonalThomasMatrix(p_a, p_b, p_c, zero_v, 0.0, 1.0);
        }


        // Approximate S
        std::vector<double> S_k_half = getApproximateSkHalf(S_k, alpha, f, s_a, s_b, s_c, s_A, s_B, t_step, V_max, K_m,
                                                            C1, q, delta);
        S_k = getNextFromHalfValues(S_k, S_k_half);
        S_k.at(S_k.size() - 1) = S_0;


        // Approximate P
        std::vector<double> P_k_half = getApproximatePkHalf(P_k, S_k_half, alpha, g, p_a, p_b, p_c, p_B, t_step, V_max,
                                                            K_m, C2, q);
        P_k = getNextFromHalfValues(P_k, P_k_half);
        P_k.at(0) = 0.0;


        // Calculate current near electrode
        I.push_back(
                n_e * F * D_p[0] * (-(p0 * P_k[0]) + (p1 * P_k[1]) - (p2 * P_k[2]))
        );

        if (i == 1) {
            exportMultiVector("S1", {"x", "S"}, {x, S_k}, 15);
            exportMultiVector("P1", {"x", "P"}, {x, P_k}, 15);

        } else if (i == t.size() - 2) {
            exportMultiVector("S", {"x", "S"}, {x, S_k}, 15);
            exportMultiVector("P", {"x", "P"}, {x, P_k}, 15);
        }
    }

    return I;
}
