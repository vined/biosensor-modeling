#ifndef BIOSENSOR_MODELING_PARAMETERS_UTILS_H
#define BIOSENSOR_MODELING_PARAMETERS_UTILS_H

#endif //BIOSENSOR_MODELING_PARAMETERS_UTILS_H


struct grid_parameters {
    // Width of bio-sensor parts widths
    double d_e;
    double d_m;
    // Width and time matrix parameters
    int N_b;
    int T;
    int M;

    grid_parameters() {}
    grid_parameters(double _d_e, double _d_m, int _N_b, int _T, int _M) {
        d_e = _d_e;
        d_m = _d_m;
        N_b = _N_b;
        T = _T;
        M = _M;
    }

    std::string toString() {
        std::string str = "Grid parameters: ";
        str += "d_e=" + std::to_string(d_e) + ", "
               + "d_m=" + std::to_string(d_m) + ", "
               + "N_b=" + std::to_string(N_b) + ", "
               + "T=" + std::to_string(T) + ", "
               + "M=" + std::to_string(M);

        return str;
    }
};

grid_parameters getDemoModeGridParameters();
grid_parameters parseGridParameters(int argc, char *argv[]);

