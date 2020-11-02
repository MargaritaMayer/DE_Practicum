#include "euler_method.h"

double Euler_Method::local_formula(double x, double y) {
    return y + (X - x0) / N * f(x, y);
}

Euler_Method::Euler_Method(){
    set_data();
}
