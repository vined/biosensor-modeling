#include <iostream>

using namespace std;

#include "values-net.h"

int main() {

    cout.precision(15);
    cout << "Size of int : " << sizeof(int) << endl;
    cout << "Size of long int : " << sizeof(long int) << endl;
    cout << "Size of double : " << sizeof(double) << endl;

    cout << generateNonLinearValuesNet(4, 5, 100).size() << endl;

    return 0;
}
