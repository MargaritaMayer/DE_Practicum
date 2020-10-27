#ifndef RUNGE_KUTTA_METHOD_H
#define RUNGE_KUTTA_METHOD_H
#include "num_method.h"

class Runge_Kutta_Method : public Num_Method {
private:
    double local_formula(double x, double y);

public:
    void calculate_values();
    Runge_Kutta_Method();
};

#endif // RUNGE_KUTTA_METHOD_H
