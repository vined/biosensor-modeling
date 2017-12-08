#ifndef BIOSENSOR_MODELING_PARAMETERS_UTILS_H
#define BIOSENSOR_MODELING_PARAMETERS_UTILS_H

#include <cmath>
#include <string>

struct parameters {
    // Width of bio-sensor parts widths
    double d_e;
    double d_m;
    // Width and time mesh parameters
    unsigned N_b;
    unsigned T;
    unsigned M;
    // Model parameters
    double Dse;
    double Dsm;
    double Dpe;
    double Dpm;
    double C1;
    double C2;
    double Vmax;
    double Km;
    double S0;
    unsigned L;
    unsigned ne;

    parameters() {}

    parameters(
            double _d_e,
            double _d_m,
            int _N_b,
            int _T,
            int _M,

            double _Dse,
            double _Dsm,
            double _Dpe,
            double _Dpm,
            double _C1,
            double _C2,
            double _Vmax,
            double _Km,
            double _S0,
            unsigned _L,
            unsigned _ne
    ) {
        d_e = _d_e * pow(10, -6);
        d_m = _d_m * pow(10, -6);
        N_b = _N_b;
        T = _T;
        M = _M;

        Dse = _Dse * pow(10, -12);
        Dsm = _Dsm * pow(10, -12);
        Dpe = _Dpe * pow(10, -12);
        Dpm = _Dpm * pow(10, -12);
        C1 = _C1;
        C2 = _C2;
        Vmax = _Vmax;
        Km = _Km;
        S0 = _S0;
        L = _L;
        ne = _ne;
    }

    std::string toString() {
        std::string str = "Parameters: ";
        str += "d_e=" + std::to_string(d_e) + ", "
               + "d_m=" + std::to_string(d_m) + ", "
               + "N_b=" + std::to_string(N_b) + ", "
               + "T=" + std::to_string(T) + ", "
               + "M=" + std::to_string(M) + ", "

               + "Dse=" + std::to_string(Dse) + ", "
               + "Dsm=" + std::to_string(Dsm) + ", "
               + "Dpe=" + std::to_string(Dpe) + ", "
               + "Dpm=" + std::to_string(Dpm) + ", "
               + "C1=" + std::to_string(C1) + ", "
               + "C2=" + std::to_string(C2) + ", "
               + "Vmax=" + std::to_string(Vmax) + ", "
               + "Km=" + std::to_string(Km) + ", "
               + "S0=" + std::to_string(S0) + ", "
               + "L=" + std::to_string(L) + ", "
               + "ne=" + std::to_string(ne);

        return str;
    }
};

parameters readParameters(std::string);

std::vector<double> get_alpha(int de_length, int dm_length);

std::vector<double> get_D(std::vector<double> alpha, double D_e, double D_m);

#endif //BIOSENSOR_MODELING_PARAMETERS_UTILS_H
