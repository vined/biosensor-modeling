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

std::vector<double> _get_new_y(
        std::vector<double> S_k,
        std::vector<double> y_old,
        std::vector<double> x,
        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> alpha,
        std::vector<double> f,
        double t_step,
        double V_max,
        double K_m,
        double C1,
        double q
) {
    std::vector<double> F = _get_F(t_step, V_max, K_m, S_k, y_old, alpha, f);
//    std::cout << "F size:" << F.size() << std::endl;
//    std::cout << "F:" << std::endl;
//    printVector(F, 0);

//    std::vector<double> A = solveCustomisedTridiagonalThomasMatrix(a, b, c, getZeroVector(a.size()), 0.0, 1.0, 1.0, 0.0);
//    std::vector<double> B = solveCustomisedTridiagonalThomasMatrix(a, b, c, getZeroVector(a.size()), 0.0, 0.0, 0.0, 1.0);
//    std::vector<double> Y = solveCustomisedTridiagonalThomasMatrix(a, b, c, F, 0.0, 0.0, 0.0, 0.0);
    std::vector<double> A = solveCustomisedTridiagonalThomasMatrix3(a, b, c, getZeroVector(a.size()), 1.0, 0.0);
    std::vector<double> B = solveCustomisedTridiagonalThomasMatrix3(a, b, c, getZeroVector(a.size()), 0.0, 1.0);
    std::vector<double> Y = solveCustomisedTridiagonalThomasMatrix3(a, b, c, F, 0.0, 0.0);

//    std::cout << "A size:" << A.size() << std::endl;
//    std::cout << "A:" << std::endl;
//    printVector(A, 0);
//    std::cout << "B size:" << B.size() << std::endl;
//    std::cout << "B:" << std::endl;
//    printVector(B, 0);
//
//    std::cout << "Y size:" << Y.size() << std::endl;
//    std::cout << "Y:" << std::endl;
//    printVector(Y, 0);

    return _get_new_approximations(y_old, A, B, Y, q);
}

std::vector<double> getApproximateSkHalf(
        std::vector<double> S_k,
        std::vector<double> D_s,
        std::vector<double> x,
        std::vector<double> alpha,
        std::vector<double> f,
        double t_step,
        double V_max,
        double K_m,
        double C1,
        double q,
        double delta
) {

    std::vector<double> y_old(S_k);
    std::vector<double> y_new;

    std::vector<double> a = get_a(D_s, x);
    std::vector<double> b = get_b(D_s, x);
    std::vector<double> c = get_c(t_step, C1, a, b);

    double progress = 0;
    double residual = 0;
    double allowed_error = 0;
    int i = 0;

//    std::cout << "S_k:" << std::endl;
//    printVector(S_k, 0);
//    std::cout << std::endl;

//    std::cout << "a:" << std::endl;
//    printVector(a, 0);
//    std::cout << "b:" << std::endl;
//    printVector(b, 0);
//    std::cout << "c:" << std::endl;
//    printVector(c, 0);

    do {
        if (i > MAX_ITERATIONS) {
//        if (i > 10) {
//            break;
            throw 100;
        }
        i++;

//        std::cout << "y_old:" << std::endl;
//        printVector(y_old, 0);

        y_new = _get_new_y(S_k, y_old, x, a, b, c, alpha, f, t_step, V_max, K_m, C1, q);

//        std::cout << "y_new:" << std::endl;
//        printVector(y_new, 0);

        std::vector<double> F_new = _get_F(t_step, V_max, K_m, S_k, y_new, alpha, f);

        progress = getProgress(y_new, y_old);
        residual = getResidual(y_new, a, b, c, F_new);
        allowed_error = getAllowedError(y_new, delta);
        y_old = y_new;

//        std::cout << std::endl;
//        std::cout << i << " progress " << progress << " residual " << residual << " allowed_error " << allowed_error << std::endl;
//        std::cout << std::endl;

    } while (allowed_error < progress || allowed_error < residual);

    return y_new;
}
