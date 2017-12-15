#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <utility>

#include "approximations-utils.h"
#include "s-approximations.h"
#include "p-approximations.h"
#include "approximations.h"
#include "parameters-utils.h"


#define F 96485.3365 // Faraday constant (C/mol)

double getCurrentTimeDerivative(
        double t1, double t2, double t3,
        double i1, double i2, double i3
) {

    double a1 = (t3 - t2) / (t1 - t2) * (t1 - t3);
    double a2 = (t3 - t1) / (t2 - t1) * (t2 - t3);
    double a3 = (2 * t3 - t1 - t2) / (t3 - t1) * (t3 - t2);

    double cd = a1 * i1 + a2 * i2 + a3 * i3;

    if (cd < 0) {
        std::cout << "Current density is not increasing monotonically" << std::endl;
        throw 400;
    }

    return cd;
}

std::pair<double, double> approximate_I(
        std::vector<double> x,
        std::vector<double> t,
        std::vector<double> D_s,
        std::vector<double> D_p,
        std::vector<double> alpha,
        std::vector<double> f,
        std::vector<double> g,
        grid_parameters grid_params,
        model_parameters params,
        double C1,
        double C2,
        double q,
        double delta
) {
    double p0 = (x[1] + x[2]) / (x[1] * x[2]);
    double p1 = x[2] / (x[1] * (x[2] - x[1]));
    double p2 = x[1] / (x[2] * (x[2] - x[1]));

    std::vector<double> I;
    I.push_back(0.0);
    std::vector<double> itks;
    itks.push_back(0.0);

    // S and P initial values
    std::vector<double> S_k = getExponentialS0(params.S0, grid_params.d_e + grid_params.d_m, params.L, x);
    std::vector<double> P_k = getZeroVector(x.size());

    // Current density initial value
    double max_itk = 0;

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

    for (int i = 0; i < t.size() - 1; i++) {

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
        std::vector<double> S_k_half = getApproximateSkHalf(S_k, alpha, f, s_a, s_b, s_c, s_A, s_B, t_step,
                                                            params.Vmax, params.Km, C1, q, delta);
        S_k = getNextFromHalfValues(S_k, S_k_half);
        S_k.at(S_k.size() - 1) = params.S0;


        // Approximate P
        std::vector<double> P_k_half = getApproximatePkHalf(P_k, S_k_half, alpha, g, p_a, p_b, p_c, p_B, t_step,
                                                            params.Vmax, params.Km, C2, q);
        P_k = getNextFromHalfValues(P_k, P_k_half);
        P_k.at(0) = 0.0;


        // Calculate current near electrode
        double it = params.ne * F * D_p[0] * (-(p0 * P_k[0]) + (p1 * P_k[1]) - (p2 * P_k[2]));
        I.push_back(it);


        if (i > 0) {
            double itk = (I[i] - I[i - 1]) / t_step;
            itks.push_back(itk);

            if (itk < 0) {
                std::cout << "Current density is not increasing monotonically" << std::endl;
                throw 400;
            }

            if (itk > max_itk) {
                max_itk = itk;
            }


            if (itk / max_itk < 0.001) {
                return std::pair<double, double>(it, t[i]);
            }
        }
    }

    return std::pair<double, double>(0.0, 0.0);
}
