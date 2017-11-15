#include <cmath>
#include <vector>
#include <algorithm>

#include "s-approximations.h"
#include "approximations-utils.h"


#define MAX_ITERATIONS = 1000

std::vector<double> _get_F(
        double t_step,
        double V_max,
        double K_m,
        std::vector<double> S_k,
        std::vector<double> y,
        std::vector<int> alpha,
        std::vector<double> f
) {
    std::vector<double> F;

    for (int i = 1; i < y.size() - 1; i++) {
        F.push_back(
                (2 * S_k[i] / t_step) - ( (alpha[i] * V_max * y[i]) / (K_m + y[i]) ) + getMidVal(f, i, true)
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
    double a = ((1 + q)^2) * (S_0 * B[1] + Y[1]) - (S_0 * B[2]) - Y[2];
    double b = ((1 + q)^2) * (1 - A[1]) + A[2] - 1;

    return a/b;
}

std::vector<double> _get_new_approximations(
        std::vector<double> S_k,
        std::vector<double> y_old,
        std::vector<double> A,
        std::vector<double> B,
        std::vector<double> Y,
        double t_step,
        double q,
        double delta
) {

    std::vector<double> y_new;
    int N = S_k.size()-1;
    double S_0 = S_k[N];

    double y0 = _get_new_y_0(A, B, Y, S_0, q);

    y_new.push_back(yN);
    for (int i = 1; i < N-1; i++) {
        y_new.push_back(
                y0 * A[i] + yN * B[i] + Y[i]
        );
    }
    y_new.push_back(S_0);

    return y_new;
}

std::vector<double> _get_new_y(
        std::vector<double> S_k,
        std::vector<double> D_s,
        std::vector<double> x,
        std::vector<int> alpha,
        std::vector<double> f,
        double t_step,
        double V_max,
        double K_m,
        double C1,
        double q,
        double delta
) {
    std::vector<double> a = get_a(D_s, x);
    std::vector<double> b = get_b(D_s, x);
    std::vector<double> c = get_c(t_step, C1, a, b);
    std::vector<double> F = _get_F(t_step, V_max, K_m, S_k, y_old, alpha, f);

    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> Y;
    A.push_back(1);
    B.push_back(0);
    Y.push_back(0);

    std::vector<double> tmp_AB = solveTridiagonalMatrix(a, c, b, getZeroVector(b.size()));
    std::vector<double> tmp_Y = solveTridiagonalMatrix(a, c, b, negateVector(F));

    A.insert(A.back(), tmp_AB);
    A.insert(B.back(), tmp_AB);
    Y.insert(Y.back(), tmp_Y);
    A.push_back(0);
    B.push_back(1);
    Y.push_back(0);

    return _get_new_approximations(S_k, y_old, A, B, Y, t_step, q, delta);
}

std::vector<double> _get_next_S_k(
        std::vector<double> S_k,
        std::vector<double> D_s,
        std::vector<double> x,
        std::vector<int> alpha,
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
    double progress = 0;
    double residual = 0;
    double allowed_error = 0;
    int i = 0;

    do {
        if (i > MAX_ITERATIONS) {
            throw 100;
        }
        i++;

        y_new = _get_new_y(S_k, D_s, x, alpha, f, t_step, V_max, K_m, C1, q, delta);
        std::vector<double> F_new = _get_F(t_step, V_max, K_m, S_k, y_old, alpha, f);

        progress = getProgress(y_new, y_old);
        residual = getResidual(y_new, a, b, c, F_new);
        allowed_error = getAllowedError(y_new, delta);

    } while (allowed_error > progress && allowed_error > residual);

    return getNextFromHalfValues(S_k, y_new);
}

std::vector<std::vector<double>> approximate_S(
        std::vector<double> D_s,
        std::vector<double> x,
        std::vector<double> t,
        std::vector<int> alpha,
        std::vector<double> f,
        double S_0,
        double V_max,
        double K_m,
        double C1,
        double q,
        double delta
) {

    std::vector<std::vector<double>> S;
    std::vector<double> S_k = get_zero_vector(x.size()-1);
    S_k.push_back(S_0);

    for (int i = 1; i < t.size(); i++) {
        std::vector<double> S_i = _get_next_S_k(S_k, D_s, x, alpha, f, t_step, V_max, K_m, C1, q, delta);
        S.push_back(S_i);
        S_k(S_i);
    }

    return S;
}
