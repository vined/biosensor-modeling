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

    return 0;
}
