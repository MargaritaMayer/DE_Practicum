#include "own_exact_solution.h"
#include <cmath>

void Own_Exact_Solution::calculate_values() {
    double x;
    for (int i = 0; i < N; i++) {
        x = x0 + (X - x0) / N * i;
        y[i] = x * x * exp(3 - 3 / x);
    }
}

Own_Exact_Solution::Own_Exact_Solution(){
    Grid();
}
