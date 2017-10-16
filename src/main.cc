#include <iostream>
#include <fstream>
#include <vector>

#include "values-net.h"
#include "machine-precision.h"
#include "time-intervals.h"

using namespace std;


#define OUTPUT "../out/"

void printVector(vector<double> vect, int max);
void exportVector(string name, vector<double> vect);

int main() {

    // Generic system information
    int mp = getMachinePrecision();
    cout.precision(mp-1);
    cout << "Machine precision : " << mp << endl;
    cout << "Size of double : " << sizeof(double) << endl;

    // Creating x and t values net
    cout << "Generating x values" << endl;
    vector<double> x = generateNonLinearValuesNet(4, 5, 100);
    cout << "Done, x values size: " << x.size() << endl;
    exportVector("x", x);

    cout << "Generating t values" << endl;
    vector<double> t = getTimeIntervals(1000, 1000000, mp);
    cout << "Done, t values size: " << t.size() << endl;
    exportVector("t", t);

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

void exportVector(string name, vector<double> vect) {

    string fileName = OUTPUT + name + ".dat";

    cout << "Exporting " << fileName << "";

    ofstream dat;
    dat.open(fileName);

    dat << "# " <<name << endl;

    for (double val : vect) {
        dat << val << endl;
    }

    dat.close();
    cout << "Exporting " << fileName << " done.";
}
