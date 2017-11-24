#include <vector>

using namespace std;


struct values_net_params {
    double d_e;
    double d_m;
    double h_max;
    double h_I_max;
    double q;
    int N_b;
    int N_i;
    int N_theta;
    double N;
};

vector<double> _get_I(int N_i, double q, double I_length);
vector<double> _get_d_block(vector<double> I, vector<double> rev_I, vector<double> theta, bool include_theta);
vector<double> _get_theta_block(int N_theta, double h);
vector<double> _get_steps(values_net_params params);

values_net_params getNonLinearValuesNetParams(double d_e, double d_m, int N_b);
vector<double> generateNonLinearValuesNet(values_net_params params);

pair<int, int> get_de_dm_segments_lengths(values_net_params params);
