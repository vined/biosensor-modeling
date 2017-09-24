#include <iostream>
#include <array>

using namespace std;

#include "exponent-values-net-generator.h"

int main() {

    cout.precision(15);
    cout << "Size of int : " << sizeof(int) << endl;
    cout << "Size of long int : " << sizeof(long int) << endl;
    cout << "Size of double : " << sizeof(double) << endl;

    // Test _get_N
    cout << "When N_b is 10000, N should be 92110, N actually is: " << _get_N(10000) << endl;

    // Test <array>
    array<double, 3> res;
    for (int i=0; i<res.size(); i++) {
        res[i] = i/3.0;
    }

    for (double elem : res)
        cout << elem << endl;

    return 0;
}
