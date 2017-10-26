#include <vector>

double _get_progress(std::vector<double> y_new, std::vector<double> y_old);

double _get_residual(
    std::vector<double> y,
    std::vector<double> a,
    std::vector<double> b,
    std::vector<double> c,
    std::vector<double> F
);

void findApproximations(std::vector<double> x, std::vector<double> t, double delta);
