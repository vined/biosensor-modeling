#include <vector>

std::vector<double> getApproximatePkHalf(
        std::vector<double> P_k,
        std::vector<double> S_k_half,
        std::vector<double> D_p,
        std::vector<double> x,
        std::vector<double> alpha,
        std::vector<double> g,
        double t_step,
        double V_max,
        double K_m,
        double C2,
        double q
);
