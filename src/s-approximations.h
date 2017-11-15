#include <vector>

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
);

