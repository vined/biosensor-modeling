#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "../lib/lapacke.h"

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
    for (unsigned i = 0; i < a.size(); i++) {
        unsigned yi = i + 1;

        double values[4] = {fabs(a[i]), fabs(b[i]), fabs(c[i]), fabs(F[i])};
        double *m = std::max_element(std::begin(values), std::end(values));
        double res = a[i] * y[yi - 1] - c[i] * y[yi] + b[i] * y[yi + 1] + F[i];
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
    return (v_i + v_i_half) / 2.0;
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

std::vector<double> slice(int from, int to, std::vector<double> vec) {
    std::vector<double> result;

    for (int i = from; i <= to; i++) {
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

    for (unsigned i = 0; i < prev.size(); i++) {
        result.push_back(
                2.0 * y[i] - prev[i]
        );
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
        std::vector<double> d
) {
    std::vector<double> _c;
    std::vector<double> _d;
    std::vector<double> x;

    double _ci = c[0] / b[0];
    double _di = d[0] / b[0];

    _c.push_back(_ci);
    _d.push_back(_di);

    for (unsigned i = 1; i < a.size(); i++) {
        _di = (d[i] - a[i] * _di) / (b[i] - a[i] * _ci);
        _ci = c[i] / (b[i] - a[i] * _ci);

        _d.push_back(_di);
        if (i == a.size() - 1) {
            _c.push_back(0.0);
        } else {
            _c.push_back(_ci);
        }
    }

    double xi = _di;
    x.push_back(xi);
    for (int i = _d.size() - 2; i >= 0; i--) {
        xi = _d[i] - _c[i] * xi;
        x.push_back(xi);
    }

    std::vector<double> rev_x(x.size());
    std::reverse_copy(x.begin(), x.end(), rev_x.begin());
    return rev_x;
}

std::vector<double> solveTridiagonalMatrix(
        std::vector<double> dl,
        std::vector<double> d,
        std::vector<double> du,
        std::vector<double> b
) {
    int n = b.size();
    std::vector<double> dl1 = slice(1, n, dl);
    std::vector<double> d1(d);
    std::vector<double> du1 = slice(0, n - 1, du);

    int info;
    int one = 1;
    std::vector<double> x(b);

    dgtsv_(&n, &one, &*dl1.begin(), &*d1.begin(), &*du1.begin(), &*x.begin(), &n, &info);

    if (info != 0) {
        throw 200;
    }

    return x;
}

