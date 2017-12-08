#ifndef BIOSENSOR_MODELING_APPROXIMATION_UTILS_H
#define BIOSENSOR_MODELING_APPROXIMATION_UTILS_H

#endif //BIOSENSOR_MODELING_APPROXIMATION_UTILS_H

double getProgress(std::vector<double> y_new, std::vector<double> y_old);

double getResidual(
        std::vector<double> y,
        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> F
);

double getAllowedError(std::vector<double> y, double delta);

double getMidVal(std::vector<double> v, int i, bool up);

// Vector utils
std::vector<double> getVectorWithValue(int n, double value);
std::vector<double> getZeroVector(int n);
std::vector<double> negateVector(std::vector<double> vec);

std::vector<double> getNextFromHalfValues(
        std::vector<double> prev,
        std::vector<double> y
);


std::vector<double> get_a(
        std::vector<double> D,
        std::vector<double> x
);
std::vector<double> get_b(
        std::vector<double> D,
        std::vector<double> x
);
std::vector<double> get_c(
        double t_step,
        double C,
        std::vector<double> a,
        std::vector<double> b
);

std::vector<double> solveTridiagonalThomasMatrix(
        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> F,
        double gamma1,
        double gamma2
);
