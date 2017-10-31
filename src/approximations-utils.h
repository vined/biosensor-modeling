#ifndef BIOSENSOR_MODELING_APPROXIMATION_UTILS_H
#define BIOSENSOR_MODELING_APPROXIMATION_UTILS_H

#endif //BIOSENSOR_MODELING_APPROXIMATION_UTILS_H

double _get_progress(std::vector<double> y_new, std::vector<double> y_old);

double _get_residual(
        std::vector<double> y,
        std::vector<double> a,
        std::vector<double> b,
        std::vector<double> c,
        std::vector<double> F
);

double _get_allowed_error(std::vector<double> y, double delta);

double _get_mid_val(std::vector<double> v, int i, bool up);
