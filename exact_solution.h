#ifndef EXACT_SOLUTION_H
#define EXACT_SOLUTION_H
#include "grid.h"

class Exact_Solution : public Grid {
protected:
    double* y = new double[N];

public:
    double operator[](size_t i);
    virtual void calculate_values() = 0;
//	friend class Ploting;
};

#endif // EXACT_SOLUTION_H
