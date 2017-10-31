#include <cmath>
#include <vector>
#include <algorithm>

#include "s-approximations.h"
#include "approximations-utils.h"


#define MAX_ITERATIONS = 1000

std::vector<double> _get_a(
        std::vector<double> D_s,
        std::vector<double> x,
        std::vector<double> h
) {
    std::vector<double> a;

    for (int i = 1; i < x.size() - 1; i++) {
        a.push_back(
                (2 * _get_mid_val(D_s, i, false)) / (h[i - 1] * (x[i + 1] - x[i - 1]))
        );
    }

    return a;
}

std::vector<double> _get_b(
        std::vector<double> D_s,
        std::vector<double> x,
        std::vector<double> h
) {
    std::vector<double> b;

    for (int i = 1; i < x.size() - 1; i++) {
        b.push_back(
                (2 * _get_mid_val(D_s, i, true)) / (h[i] * (x[i + 1] - x[i - 1]))
        );
    }

    return b;
}

std::vector<double> _get_c(
        double t_step,
        double C1,
        std::vector<double> a,
        std::vector<double> b
) {
    std::vector<double> c;

    for (int i = 1; i < a.size() - 1; i++) {
        c.push_back(
                a[i] + b[i] + (2 / t_step) + C1
        );
    }

    return c;
}

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
                (2 * S_k[i] / t_step) - ( (alpha[i] * V_max * y[i]) / (K_m + y[i]) ) + _get_mid_val(f, i, true)
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
    int N = S_k.size();
    double S_0 = S_k[N-1];

    double y0 = _get_new_y_0(A, B, Y, S_0, q);

    y_new.push_back(yN);
    for (int i = 1; i < N - 1; i++) {
        y_new.push_back(
                y0 * A[i] + yN * B[i] + Y[i]
        );
    }
    y_new.push_back(S_0);

    return y_new;
}

void get_next_S(
        std::vector<double> S_k,
        std::vector<double> D_s,
        std::vector<double> x,
        std::vector<double> h,
        std::vector<int> alpha,
        std::vector<double> f,
        double t_step,
        double V_max,
        double K_m,
        double C1,
        double q,
        double delta
) {

    std::vector<double> y_old = S_k;
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

        std::vector<double> a = _get_a(D_s, x, h);
        std::vector<double> b = _get_b(D_s, x, h);
        std::vector<double> c = _get_c(t_step, C1, a, b);
        std::vector<double> F = _get_F(t_step, V_max, K_m, S_k, y_old, alpha, f);

        // ToDo calculate A,B,Y with lapac

        y_new = _get_new_approximations(S_k, y_old, A, B, Y, t_step, q, delta);

        std::vector<double> F_new = _get_F(t_step, V_max, K_m, S_k, y_old, alpha, f);

        progress = _get_progress(y_new, y_old);
        residual = _get_residual(y_new, a, b, c, F_new);
        allowed_error = _get_allowed_error(y_new, delta);

    } while (allowed_error > progress && allowed_error > residual);

    return y_new;
}

void approximate_s(
        std::vector<double> S_k,
        std::vector<double> D_s,
        std::vector<double> x,
        std::vector<double> h,
        std::vector<double> t,
        std::vector<int> alpha,
        std::vector<double> f,
        double V_max,
        double K_m,
        double C1,
        double q,
        double delta
) {

    // ToDo for t get S_i
}
