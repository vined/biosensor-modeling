#include <cmath>

#include "machine-precision.h"

using namespace std;


#define MAX_ITERATIONS 100

int getMachinePrecision() {
    double value = 10;

    for (int i = 2; i < MAX_ITERATIONS; i++) {
        int exp = -i;
        double epsilon = pow(value, exp);
        if (value == (value + epsilon)) {
            return exp;
        }
    }
    return 0;
}
