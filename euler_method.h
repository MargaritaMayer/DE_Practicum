#ifndef EULER_METHOD_H
#define EULER_METHOD_H
#include "num_method.h"

class Euler_Method : public Num_Method {
private:
    double local_formula(double x, double y);

public:
    void calculate_values();
    Euler_Method();
};

#endif // EULER_METHOD_H
