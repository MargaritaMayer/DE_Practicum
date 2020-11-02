#include "own_exact_solution.h"
#include <cmath>

void Own_Exact_Solution::calculate_values() {
    maximal = y0;
    minimal = y0;
    double x;
    for (int i = 0; i < N + 1; i++) {
        x = x0 + (X - x0) / N * i;
        y[i] = x * x * exp(3 - 3 / x);
        maximal = maximal < y[i] ? y[i] : maximal;
        minimal = minimal > y[i] ? y[i] : minimal;
    }
}

Own_Exact_Solution::Own_Exact_Solution(){
    set_data();
}
