#include <vector>


std::vector<double> approximate_I(
        std::vector<double> x,
        std::vector<double> t,
        std::vector<double> D_s,
        std::vector<double> D_p,
        std::vector<double> alpha,
        std::vector<double> f,
        std::vector<double> g,
        double S_0,
        double V_max,
        double K_m,
        double C1,
        double C2,
        int n_e,
        double q,
        double delta
);
