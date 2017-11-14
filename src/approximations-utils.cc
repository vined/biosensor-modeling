#include <cmath>
#include <vector>
#include <algorithm>

#include "approximations-utils.h"


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
    // from i to N - 1, not taking first and last element
    for (unsigned i = 1; i < y.size() - 1; i++) {

        double values[4] = {abs(a[i]), abs(b[i]), abs(c[i]), abs(F[i])};
        double *m = std::max_element(std::begin(values), std::end(values));
        double res = a[i] * y[i - 1] - c[i] * y[i] + b[i] * y[i + 1] + F[i];
        double residual = abs(res) / *m;

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
    double v_i = v[i];
    double v_i_half;

    if (up) {
        v_i_half = v[i + 1];
    } else {
        v_i_half = v[i - 1];
    }
    return (v_i + v_i_half) / 2;
}

std::vector<double> getZeroVector(int n) {
    std::vector<double> d(n);

    for(int i = 0; i < n; i++) {
        d[i] = 0.0;
    }

    return d;
}

std::vector<double> slice(int from, int to, std::vector<double> vec) {
    std::vector<double> result;

    for(int i = from; i <= to; i++) {
        result.push_back(vec[i]);
    }

    return result;
}

std::vector<double> negateVector(std::vector<double> vec) {
    std::vector<double> result;

    for (double val : vec) {
        result.push_back(-val);
    }

    return result;
}

std::vector<double> getNextFromHalfValues(
        std::vector<double> prev,
        std::vector<double> y
) {
    std::vector<double> result;

    for(unsigned i = 0; i < prev.size(); i++) {
        result.push_back(
                2*y[i] - prev[i]
        );
    }

    return result;
}
