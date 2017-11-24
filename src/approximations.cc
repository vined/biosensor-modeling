#include <cmath>
#include <vector>
#include <algorithm>

#include "approximations-utils.h"
#include "s-approximations.h"
#include "p-approximations.h"
#include "approximations.h"


#define F 96485.3365 // Faraday constant (C/mol)

I_approximation_result approximate_I(
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

    std::vector<std::vector<double>> S;
    std::vector<std::vector<double>> P;

    // S initial values
    std::vector<double> S_k = getZeroVector(x.size()-1);
    S_k.push_back(S_0);
    S.push_back(S_k);

    // P initial values
    std::vector<double> P_k = getZeroVector(x.size());
    P.push_back(P_k);

    for (int i = 1; i < t.size()-1; i++) {
        double t_step = t[i+1] - t[i];

        // Approximate S
        std::vector<double> S_k_half = getApproximateSkHalf(S_k, D_s, x, alpha, f, t_step, V_max, K_m, C1, q, delta);
        std::vector<double> S_i = getNextFromHalfValues(S_k, S_k_half);

        S.push_back(S_i);
        S_k = S_i;

        // Approximate P
        std::vector<double> P_k_half = getApproximatePkHalf(P_k, S_k_half, D_p, x, alpha, g, t_step, V_max, K_m, C2, q);
        std::vector<double> P_i = getNextFromHalfValues(P_k, P_k_half);

        P.push_back(P_i);
        P_k = P_i;

        // Calculate current near electrode
        I.push_back(
                n_e * F * D_p[0] * ( - (p0 * P_k[0]) + (p1 * P_k[1]) - (p2 * P_k[2]) )
        );
    }

    return I_approximation_result(I, S, P);
}
