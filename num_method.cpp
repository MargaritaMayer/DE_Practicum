#include "num_method.h"
#include <cmath>

double Num_Method::f(double x, double y) {
    return (3 * y + 2 * x * y) / x / x;
}

double Num_Method::operator[](size_t i) {
    return y[i];
}

double Num_Method::find_LTE(double exact, int i) {
    return abs(y[i + 1] - local_formula(i, exact));
}
