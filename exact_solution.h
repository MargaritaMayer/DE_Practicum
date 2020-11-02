#ifndef EXACT_SOLUTION_H
#define EXACT_SOLUTION_H
#include <QVector>
#include "grid.h"

class Exact_Solution : public Grid {
protected:
    QVector<double> y;
    double minimal, maximal;

public:
    QVector<double> get_y();
    double get_minimal();
    double get_maximal();
    void set_data (double x0 = 1, double y0 = 1, double X = 6, int N = 600);
    virtual void calculate_values() = 0;
};

#endif // EXACT_SOLUTION_H
