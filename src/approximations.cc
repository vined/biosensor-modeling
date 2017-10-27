#include <cmath>
#include <vector>
#include <algorithm>


// Todo move to utils
double _get_progress(std::vector<double> y_new, std::vector<double> y_old) {

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
double _get_residual(
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

double _get_allowed_error(std::vector<double> y, double delta) {
    double max = *std::max_element(y.begin(), y.end());
    return max * delta;
}

double _get_mid_val(std::vector<double> v, int i, bool up) {
    double v_i = v[i];
    double v_i_half;

    if (up) {
        v_i_half = v[i + 1];
    } else {
        v_i_half = v[i - 1];
    }
    return (v_i + v_i_half) / 2;
}


// Todo: move to s-approximations.cc
std::vector<double> _get_a(std::vector<double> D_s, std::vector<double> x, std::vector<double> h) {
    std::vector<double> a;

    for (int i = 1; i < x.size() - 1; i++) {
        a.push_back(
                (2 * _get_mid_val(D_s, i, false)) / (h[i - 1] * (x[i + 1] - x[i - 1]))
        );
    }

    return a;
}

std::vector<double> _get_b(std::vector<double> D_s, std::vector<double> x, std::vector<double> h) {
    std::vector<double> b;

    for (int i = 1; i < x.size() - 1; i++) {
        b.push_back(
                (2 * _get_mid_val(D_s, i, true)) / (h[i] * (x[i + 1] - x[i - 1]))
        );
    }

    return b;
}

std::vector<double> _get_c(double t_step, double C1, std::vector<double> a, std::vector<double> b) {
    std::vector<double> c;

    for (int i = 1; i < x.size() - 1; i++) {
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
                (2 * S_k[i] / t_step) - ( (alpha[i] * V_max * y[i]) / (K_m + y) ) + _get_mid_val(f, i, true)
        );
    }

    return F;
}

std::vector<double> _get_new_approximations(std::vector<double> y_old, double t_step, double delta) {

    vector<double> y_new;
    double y0 = y_old[0];
    double yN = y_old[y_old.size() - 1];

    for (y_old_i : y_old) {
//        y_new_i =
    }
}

void findApproximations(std::vector<double> x, std::vector<double> t, double delta) {

}
