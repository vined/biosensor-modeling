#include <cmath>
#include <vector>
#include <algorithm>

#include "time-intervals.h"

using namespace std;


vector<double> _get_non_linear_interval(int m, double tau) {

    vector<double> result;

    for (int i=m; i > 0; i--) {
        result.push_back(tau/pow(2,i));
    }

    return result;
}

vector<double> _get_linear_interval(int M, double tau) {

    vector<double> result;

    for (int i=1; i <= M; i++) {
        result.push_back(tau*i);
    }

    return result;
}

/*
T - maximum model time
M - steps count
mp - machine precision
*/
vector<double> getTimeIntervals(int T, int M, int mp) {

    double tau = T/(double)M;
    double tau_min = pow(10, mp) * 100;

    int m = floor( log2( tau/tau_min ));

    // Interval starts with zero
//    vector<double> start = _get_non_linear_interval(m, tau);
    vector<double> end = _get_linear_interval(M, tau);
    vector<double> result = {0.0};

//    result.insert(result.end(), start.begin(), start.end());
    result.insert(result.end(), end.begin(), end.end());
    return result;
}

