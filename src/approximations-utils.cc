#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "approximations-utils.h"
#include "output-utils.h"


double getProgress(std::vector<double> y_new, std::vector<double> y_old) {

    double max_diff = 0;
    for (unsigned i = 0; i < y_new.size(); i++) {
        double diff = std::abs(y_new[i] - y_old[i]);

        if (diff > max_diff) {
            max_diff = diff;
        }
    }
    return max_diff;
}

// Backward error
double getResidual(
        std::vector<double> y,
        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> F
) {

    double max_residual = 0;
    for (unsigned i = 0; i < a.size(); i++) {
        unsigned yi = i + 1;

        double values[4] = {fabs(a[i]), fabs(b[i]), fabs(c[i]), fabs(F[i])};
        double *m = std::max_element(std::begin(values), std::end(values));
        double res = a[i] * y[yi - 1] - c[i] * y[yi] + b[i] * y[yi + 1] + F[i];
        double residual = fabs(res) / *m;

        if (residual > max_residual) {
            max_residual = residual;
        }
    }

    return max_residual;
}

double getAllowedError(std::vector<double> y, double delta) {
    double max = *std::max_element(y.begin(), y.end());
    return max * delta;
}

double getMidVal(std::vector<double> v, int i, bool up) {

    if (up) {
        return (v[i] + v[i + 1]) / 2.0;
    } else {
        return (v[i] + v[i - 1]) / 2.0;
    }
}

std::vector<double> getNextFromHalfValues(
        std::vector<double> prev,
        std::vector<double> y
) {
    std::vector<double> result;

    for (unsigned i = 0; i < prev.size(); i++) {
        result.push_back(
                2.0 * y[i] - prev[i]
        );
    }

    return result;
}

std::vector<double> getVectorWithValue(int n, double value) {
    std::vector<double> d;

    for (int i = 0; i < n; i++) {
        d.push_back(value);
    }

    return d;
}

std::vector<double> getZeroVector(int n) {
    return getVectorWithValue(n, 0.0);
}

std::vector<double> negateVector(std::vector<double> vec) {
    std::vector<double> result;

    for (double val : vec) {
        result.push_back(-val);
    }

    return result;
}

std::vector<double> get_a(
        std::vector<double> D,
        std::vector<double> x
) {
    std::vector<double> a;

    for (unsigned i = 1; i < x.size() - 1; i++) {
        double h = x[i] - x[i - 1];
        a.push_back(
                (2.0 * getMidVal(D, i, false)) / (h * (x[i + 1] - x[i - 1]))
        );
    }

    return a;
}

std::vector<double> get_b(
        std::vector<double> D,
        std::vector<double> x
) {
    std::vector<double> b;

    for (unsigned i = 1; i < x.size() - 1; i++) {
        double h = x[i + 1] - x[i];
        b.push_back(
                (2.0 * getMidVal(D, i, true)) / (h * (x[i + 1] - x[i - 1]))
        );
    }

    return b;
}

std::vector<double> get_c(
        double t_step,
        double C,
        std::vector<double> a,
        std::vector<double> b
) {
    std::vector<double> c;

    for (unsigned i = 0; i < a.size(); i++) {
        c.push_back(
                a[i] + b[i] + C + (2.0 / t_step)
        );
    }

    return c;
}

std::vector<double> solveTridiagonalThomasMatrix(
        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> F,
        double gamma1,
        double gamma2
) {

    // Alpha
    // Todo OPTIMIZE: alpha can be calculated once, does not use F

    std::vector<double> alpha;
    double alpha_i = 0.0;
    alpha.push_back(alpha_i);

    for (unsigned i = 0; i < a.size(); i++) {
        alpha_i = b[i] / (c[i] - a[i] * alpha_i);
        alpha.push_back(alpha_i);
    }

    // Beta

    std::vector<double> beta;
    double beta_i = gamma1;
    beta.push_back(beta_i);

    for (unsigned i = 0; i < a.size(); i++) {
        beta_i = (a[i] * beta_i + F[i]) / (c[i] - a[i] * alpha[i]);
        beta.push_back(beta_i);
    }

    // y

    unsigned N = F.size()+2;
    std::vector<double> y(N);

    double y_i = gamma2;
    y[N-1] = y_i;

    for (int i = alpha.size() - 1; i >= 0; i--) {
        y_i = alpha[i] * y_i + beta[i];
        y[i] = y_i;
    }

    return y;

    // y reversed - takes a bit longer
//
//    std::vector<double> y_rev;
//    double y_i = gamma2;
//    y_rev.push_back(y_i);
//
//    for (int i = alpha.size() - 1; i >= 0; i--) {
//        y_i = alpha[i] * y_i + beta[i];
//        y_rev.push_back(y_i);
//    }
//
//    std::vector<double> y(y_rev.size());
//    std::reverse_copy(y_rev.begin(), y_rev.end(), y.begin());
//
//    return y;
}
