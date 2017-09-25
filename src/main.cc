#include <iostream>
#include <array>

using namespace std;

#include "exponent-intervals.h"

int main() {

    cout.precision(15);
    cout << "Size of int : " << sizeof(int) << endl;
    cout << "Size of long int : " << sizeof(long int) << endl;
    cout << "Size of double : " << sizeof(double) << endl;

    // Test _get_N

    int N_b = 10000;
    double h_max = get_user_h_max(N_b);
    double q = get_q(N_b);
    cout << "When N_b is 10000, N should be 92110, N actually is: " << get_N(q, h_max) << endl;

    // Test <array>
    array<double, 3> res;
    for (int i=0; i<res.size(); i++) {
        res[i] = i/3.0;
    }

    for (double elem : res)
        cout << elem << endl;

    return 0;
}
