#ifndef IMPROVED_EULER_METHOD_H
#define IMPROVED_EULER_METHOD_H
#include "num_method.h"

class Improved_Euler_Method : public Num_Method {
private:
    double local_formula(double x, double y);

public:
    Improved_Euler_Method();
};

#endif // IMPROVED_EULER_METHOD_H
