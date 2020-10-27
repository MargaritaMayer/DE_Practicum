#include "improved_euler_method.h"


double Improved_Euler_Method::local_formula(double x, double y) {
        double h = (X - x0) / N;
        double y1 = y + h * f(x, y);
        return y + h / 2 * (f(x, y) + f(x + h, y1));
    }

void Improved_Euler_Method::calculate_values() {
    y[0] = y0;
    for (int i = 1; i < N; i++) {
        y[i] = local_formula(x0 + (X - x0) / N * i, y[i - 1]);
    }
}

Improved_Euler_Method::Improved_Euler_Method(){
    Grid();
}
