#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "../lib/lapacke.h"

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
//        std::cout << "values " << fabs(a[i]) << " " << fabs(b[i]) << " " << fabs(c[i]) << " " << fabs(F[i]) << std::endl;
//        std::cout << "*m " << *m << std::endl;
//        std::cout << "res " << res << std::endl;
//        std::cout << "residual " << residual << std::endl;

        if (residual > max_residual) {
            max_residual = residual;
        }
    }
//    std::cout << " --------------------------------- max residual " << max_residual << std::endl;
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

std::vector<double> solveCustomisedTridiagonalThomasMatrix(
        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> F,
        double kappa1,
        double gamma1,
        double y_0,
        double y_N
) {

    // Alpha

    std::vector<double> alpha;
    double alpha_i = kappa1;
    alpha.push_back(alpha_i);

    for (unsigned i = 0; i < a.size(); i++) {
        alpha_i = b[i] / (c[i] - a[i] * alpha_i);
        alpha.push_back(alpha_i);
    }

//    std::cout << "alpha:" << std::endl;
//    printVector(alpha, 0);

    // Beta

    std::vector<double> beta;
    double beta_i = gamma1;
    beta.push_back(beta_i);

    for (unsigned i = 0; i < a.size(); i++) {
        beta_i = (a[i] * beta_i + F[i]) / (c[i] - a[i] * alpha[i]);
        beta.push_back(beta_i);
    }

//    std::cout << "beta:" << std::endl;
//    printVector(beta, 0);

    // y reversed

    std::vector<double> y_rev;
    double y_i = y_N;
    y_rev.push_back(y_i);

    for (unsigned i = alpha.size() - 1; i > 0; i--) {
        y_i = alpha[i] * y_i + beta[i];
        y_rev.push_back(y_i);
    }

    y_rev.push_back(y_0);

//    std::cout << "y_rev:" << std::endl;
//    printVector(y_rev, 0);

    std::vector<double> y(y_rev.size());
    std::reverse_copy(y_rev.begin(), y_rev.end(), y.begin());

//    std::vector<double> y;
//    double y_i = y_0;
//    y.push_back(y_i);
//
//    for (unsigned i = 0; i < alpha.size(); i++) {
//        y_i = (beta[i] - y_i) / alpha[i];
//        y.push_back(y_i);
//    }
//    y.push_back(y_N);

//    std::cout << "y:" << std::endl;
//    printVector(y, 0);
    return y;
}

std::vector<double> solveCustomisedTridiagonalThomasMatrix3(
        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> F,
        double gamma1,
        double gamma2
) {

    // Alpha

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

    // y reversed

    std::vector<double> y_rev;
    double y_i = gamma2;
    y_rev.push_back(y_i);

    for (int i = alpha.size() - 1; i >= 0; i--) {
        y_i = alpha[i] * y_i + beta[i];
        y_rev.push_back(y_i);
    }

    std::vector<double> y(y_rev.size());
    std::reverse_copy(y_rev.begin(), y_rev.end(), y.begin());

    return y;
}

std::vector<double> solveCustomisedTridiagonalThomasMatrix2(
        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> F,
        double gamma1,
        double gamma2
) {
    std::vector<double> dl;
    std::vector<double> d;
    std::vector<double> du;
    std::vector<double> y;

    dl.push_back(0.0);
    dl.insert(dl.end(), a.begin(), a.end());
    dl.push_back(0.0);

    d.push_back(1.0);
    d.insert(d.end(), c.begin(), c.end());
    d.push_back(1.0);

    du.push_back(0.0);
    du.insert(du.end(), b.begin(), b.end());
    du.push_back(0.0);

    y.push_back(gamma1);
    y.insert(y.end(), F.begin(), F.end());
    y.push_back(gamma2);

    return solveTridiagonalThomasMatrix(dl, d, du, y);
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

