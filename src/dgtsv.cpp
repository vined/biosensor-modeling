#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <time.h>
#include "lib/lapacke.h"

using namespace std;

// Compile using this command:
// g++ dgtsv.cpp -llapack -o dgtsv

bool isDiagonalElement(int i, int j) {
    return i == j || i == j+1 || i+1 == j;
}

void printTriDiagonalMatrix(
        vector<double> dl,
        vector<double> d,
        vector<double> du
) {
    int n = d.size();
    cout << "Printing tridiagonal matrix with dimensions: " << n << "x" << n << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j){
            if (isDiagonalElement(i, j)) {
                    if (i == j) {
                        cout << d[i] << "\t";
                    } else if (i < j) {
                        cout << du[i] << "\t";
                    } else {
                        cout << dl[j] << "\t";
                    }
            } else {
                cout << "0\t";
            }
        }
        cout << endl;
    }
}

vector<double> getRandomVector(int n) {
    double maxr=(double)RAND_MAX;
    vector<double> d(n);

    for(int i=0; i < n; i++) {  // set a to a random matrix, i to the identity
        d[i] = rand()/maxr;
    }

    return d;
}

int main(int argc,char **argv) {

    if (argc !=2) {
        cout << "Usage: dgtsv [dimession]" << endl;
        return 0;
    }

    clock_t t1 = clock();

    int dim = atoi(argv[1]);
    srand(1);              // seed the random # generator with a known value

    vector<double> d = getRandomVector(dim);
    vector<double> du = getRandomVector(dim-1);
    vector<double> dl = getRandomVector(dim-1);
    vector<double> b = getRandomVector(dim);

    printTriDiagonalMatrix(dl, d, du);

    int info;

    cout << "matrices allocated and initialised " << double(clock() - t1) << endl;

    clock_t c2 = clock();

    int one = 1;

    dgtsv_(&dim, &one, &*dl.begin(), &*d.begin(), &*du.begin(), &*b.begin(), &dim, &info);

    clock_t c3 = clock();

    cout << "dgtsv is over after " << double(c3 - c2) << endl;
    cout << "info is " << info << endl;

    printTriDiagonalMatrix(dl, d, du);

    return 0;
}
