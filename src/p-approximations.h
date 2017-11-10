#include <vector>

std::vector<std::vector<double>> approximate_P(
        std::vector<double> D_p,
        std::vector<double> x,
        std::vector<double> h,
        std::vector<double> t,
        std::vector<int> alpha,
        std::vector<double> g,
        double P_0,
        double V_max,
        double K_m,
        double C2,
        double q,
        double delta
);

