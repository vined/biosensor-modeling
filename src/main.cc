#include <iostream>
#include <vector>

#include "values-net.h"
#include "machine-precision.h"
#include "time-intervals.h"

using namespace std;

void printVector(vector<double>, int max);

int main() {

    int mp = getMachinePrecision();
    cout.precision(mp-1);
    cout << "Machine precision : " << mp << endl;
    cout << "Size of double : " << sizeof(double) << endl;

    vector<double> net = generateNonLinearValuesNet(4, 5, 100);
    cout << net.size() << endl;
//    printVector(net);

    vector<double> time = getTimeIntervals(1000, 1000000, mp);
    cout << time.size() << endl;
//    printVector(time, time.size());

/*
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

void printVector(vector<double> vect, int max) {
    int i = 0;
    for (double val : vect) {
        if (i > max)
            return;
        cout << val << endl;
        i++;
   }
}
