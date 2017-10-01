#include <vector>

using namespace std;


struct values_net_params {
    double h_max;
    double h_I_max;
    double q;
    int N_i;
    int N_theta;
    double N;
};

vector<double> _get_I(int N_i, double q);
vector<double> _get_d_block(vector<double> I, vector<double> rev_I, vector<double> theta, bool include_theta);
vector<double> _get_theta_block(int N_theta, double h);
vector<double> _get_steps(double d_e, double d_m, values_net_params params);

values_net_params getNonLinearValuesNetParams(double d_e, double d_m, int N_b);
vector<double> generateNonLinearValuesNet(double d_e, double d_m, int N_b);
