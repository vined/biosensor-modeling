#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "exponent-intervals.h"
#include "values-range.h"
#include "values-net.h"

using namespace std;


double _get_next_h(double h_prev, double q) {
    return h_prev * q;
}

vector<double> _get_I(int N_i, double q) {

    double h = (q-1) / (pow(q, N_i) - 1);
    vector<double> I;

    for (int i=0; i<N_i; i++) {
        I.push_back(h);
        h = _get_next_h(h, q);
    }
    return I;
}

vector<double> _get_d_block(
    vector<double> I,
    vector<double> rev_I,
    vector<double> theta,
    bool include_theta)
{
    vector<double> result;

    result.insert(result.end(), I.begin(), I.end());

    if (include_theta) {
        result.insert(result.end(), theta.begin(), theta.end());
    }

    result.insert(result.end(), rev_I.begin(), rev_I.end());
    return result;
}

vector<double> _get_theta_block(int N_theta, double h) {
    vector<double> theta (N_theta, h);
    return theta;
}

vector<double> _get_steps(values_net_params params) {

    vector<double> I = _get_I(params.N_i, params.q);
    vector<double> theta = _get_theta_block(params.N_theta, params.h_I_max);
    vector<double> rev_I (I.size());
    reverse_copy(I.begin(), I.end(), rev_I.begin());

    vector<double> d1 = _get_d_block(I, rev_I, theta, params.d_e > params.d_m);
    vector<double> d2 = _get_d_block(I, rev_I, theta, params.d_e < params.d_m);

    vector<double> result;

    result.insert(result.end(), d1.begin(), d1.end());
    result.insert(result.end(), d2.begin(), d2.end());
    return result;
}

values_net_params getNonLinearValuesNetParams(double d_e, double d_m, int N_b) {

    values_net_params params;
    params.d_e = d_e;
    params.d_m = d_m;
    params.N_b = N_b;
    params.h_max = get_h_max(d_e, d_m, N_b);
    params.q = get_q(params.h_max);
    params.N_i = get_N(params.q, params.h_max);
    params.N_theta = get_N_theta(d_e, d_m, N_b);
    params.N += (4 * params.N_i) + params.N_theta;

    if (params.N_theta > 0) {
        double I_length = get_I_length(d_e, d_m);
        params.h_I_max = get_h_I_max(I_length, params.h_max);
    }

    return params;
}

vector<double> generateNonLinearValuesNet(values_net_params params) {

    vector<double> steps = _get_steps(params);

    auto biggest = std::max_element(steps.begin(), steps.end());
    std::cout << "h_max: " << *biggest << std::endl;
    auto smallest = std::min_element(steps.begin(), steps.end());
    std::cout << "h_mix: " << *smallest << std::endl;
    std::cout << "h_max/h_mix: " << *biggest / *smallest << std::endl;

    double x = 0;
    vector<double> values_net;
    values_net.push_back(x);

    for (double h : steps) {
        x += h;
        values_net.push_back(x);
    }

    return values_net;
}

