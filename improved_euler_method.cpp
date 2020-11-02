#include "improved_euler_method.h"


double Improved_Euler_Method::local_formula(double x, double y) {
        double h = (X - x0) / N;
        double y1 = y + h * f(x, y);
        return y + h / 2 * (f(x, y) + f(x + h, y1));
    }

Improved_Euler_Method::Improved_Euler_Method(){
    set_data();
}
