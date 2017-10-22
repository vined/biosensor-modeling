#include <cmath>
#include <vector>

double _get_progress(std::vector<double> nw, std::vector<double> old) {

    double max_diff = 0;
    for (int i = 0; i < nw.size(); i++) {
        double diff = std::abs(nw - old)
        if (diff > max_diff) {
            max_diff = diff;
        }
    }
}

// Backward error
double _get_residual(std::vector<double> nw, std::vector<double> old) {

}

void findApproximations(std::vector<double> x, std::vector<double> t, double delta) {

}
