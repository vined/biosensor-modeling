#include <cmath>
#include <vector>
#include <algorithm>

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

void findApproximations(std::vector<double> x, std::vector<double> t, double delta) {

}
