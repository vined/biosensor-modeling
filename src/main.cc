#include <iostream>
#include <vector>

#include "values-net.h"
#include "machine-precision.h"

using namespace std;

void printVector(vector<double>);

int main() {

    cout.precision(15);
    cout << "Size of int : " << sizeof(int) << endl;
    cout << "Size of long int : " << sizeof(long int) << endl;
    cout << "Size of double : " << sizeof(double) << endl;

    cout << "Machine presision : " << getMachinePrecision() << endl;

    vector<double> net = generateNonLinearValuesNet(4, 5, 100);
    cout << net.size() << endl;
//    printVector(net);

/*
Create values net w_t, when k(0..M)

m=floor(log2 (tau/tau_min))); where tau_min is MP*100


    - Modeling -
i - electric current
n_e - electrons count (1 or 2)
F - Faraday's constant 96485.3365 C/mol
D_Pe - difussion coefficient in ferment near electrode

main formula from 5.4.2:
i(t_k) = n_e * F * D_Pe * ( - p0 + p1 - p2 )

p0 = ( (x[1]-x[2]) / (x[1]*x[2]) ) * P[k][0]
p2 = ( x[2] / (x[1] * (x[2]-x[1])) ) * P[k][1]
p = ( x[1] / (x[2] * (x[2]-x[1])) ) * P[k][2]


Next - implement 5.6.4 and 5.6.5

*/
    return 0;
}

void printVector(vector<double> vect) {
    for (double val : vect)
        cout << val << endl;
}
