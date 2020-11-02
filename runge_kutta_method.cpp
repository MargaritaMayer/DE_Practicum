#include "runge_kutta_method.h"

double Runge_Kutta_Method::local_formula(double x, double y) {
    double h = (X - x0) / N;
    double k1 = f(x, y);
    double k2 = f(x + h / 2, y + h / 2 * k1);
    double k3 = f(x + h / 2, y + h / 2 * k2);
    double k4 = f(x + h, y + h * k3);
    return y + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
}

Runge_Kutta_Method::Runge_Kutta_Method(){
    set_data();
}
