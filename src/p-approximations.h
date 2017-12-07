#include <vector>

std::vector<double> getApproximatePkHalf(
        std::vector<double> P_k,
        std::vector<double> S_k_half,
        std::vector<double> alpha,
        std::vector<double> g,

        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> B,

        double t_step,
        double V_max,
        double K_m,
        double C2,
        double q
);
