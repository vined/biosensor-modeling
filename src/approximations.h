#include <vector>

double _get_progress(std::vector<double> y_new, std::vector<double> y_old);
double _get_residual(std::vector<double> y, double a, double b, double c, std::vector<double> F);

void findApproximations(std::vector<double> x, std::vector<double> t, double delta);
