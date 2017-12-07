#include <vector>

std::vector<double> getApproximateSkHalf(
        std::vector<double> S_k,
        std::vector<double> alpha,
        std::vector<double> f,

        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> A,
        std::vector<double> B,

        double t_step,
        double V_max,
        double K_m,
        double C1,
        double q,
        double delta
);
