#ifndef NUM_METHOD_H
#define NUM_METHOD_H
#include <QVector>
#include "grid.h"

class Num_Method : public Grid{
protected:
    QVector<double> y, GTE, LTE;
    virtual double local_formula(double x, double y) = 0;
    double f(double x, double y);
    double minimal, maximal;
    double maximalLTE, maximalGTE;

public:
    QVector<double> get_y();
    QVector<double> get_GTE();
    QVector<double> get_LTE();

    double get_minimal();
    double get_maximal();
    double get_maximalLTE();
    double get_maximalGTE();

    virtual void calculate_values();
    void calc_tranc_error(QVector<double> own);
    void set_data(double x0 = 1, double y0 = 1, double X = 6, int N = 600);
};

#endif // Num_METHOD_H
