#include <vector>
#include <utility>

#include "parameters-utils.h"


std::pair<double, double> approximate_I(
        std::vector<double> x,
        std::vector<double> t,
        std::vector<double> D_s,
        std::vector<double> D_p,
        std::vector<double> alpha,
        std::vector<double> f,
        std::vector<double> g,
        parameters params,
        double q,
        double delta,
        bool exportVectors
);
