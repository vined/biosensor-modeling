#include <iostream>
#include <vector>

#include "values-net.h"

using namespace std;


int main() {

    cout.precision(15);
    cout << "Size of int : " << sizeof(int) << endl;
    cout << "Size of long int : " << sizeof(long int) << endl;
    cout << "Size of double : " << sizeof(double) << endl;

    vector<double> net = generateNonLinearValuesNet(4, 5, 100);
    cout << net.size() << endl;

    for (double val : net)
        cout << val << endl;

/*
Create values net w_t, when k(0..M)


    - Modeling -
i - electric current
n_e - electrons count (1 or 2)
F - Faraday's constant 96485.3365 C/mol
D_Pe - difussion coeficient in ferment near electrode

main formula from 5.4.2:
i(t_k) = n_e * F * D_Pe * ( - p0 + p1 - p2 )

p0 = ( (x[1]-x[2]) / (x[1]*x[2]) ) * P[k][0]
p2 = ( x[2] / (x[1] * (x[2]-x[1])) ) * P[k][1]
p = ( x[1] / (x[2] * (x[2]-x[1])) ) * P[k][2]


Next - implement 5.6.4 and 5.6.5

*/
    return 0;
}
