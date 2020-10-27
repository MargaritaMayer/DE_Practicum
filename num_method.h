#ifndef NUM_METHOD_H
#define NUM_METHOD_H
#include "grid.h"

class Num_Method : public Grid{
protected:
    double* y = new double[N];
    virtual double local_formula(double x, double y) = 0;
    double f(double x, double y);

public:
    double operator[](size_t i);

    virtual void calculate_values() = 0;
    friend class Ploting;
    double find_LTE(double exact, int i);
};

#endif // Num_METHOD_H
