#include "num_method.h"
#include <cmath>

double Num_Method::f(double x, double y) {
    return (3 * y + 2 * x * y) / x / x;
}

QVector<double> Num_Method::get_y() {
    return y;
}

QVector<double> Num_Method::get_GTE() {
    return GTE;
}

QVector<double> Num_Method::get_LTE() {
    return LTE;
}

double Num_Method::get_minimal(){
    return minimal;
}
double Num_Method::get_maximal(){
    return maximal;
}
double Num_Method::get_maximalLTE(){
    return maximalLTE;
}
double Num_Method::get_maximalGTE(){
    return maximalGTE;
}

void Num_Method::calculate_values(){
    maximal = y0;
    minimal = y0;
    y[0] = y0;
    for (int i = 0; i < N; i++) {
        y[i + 1] = local_formula(x0 + (X - x0) / N * i, y[i]);
        maximal = maximal < y[i + 1] ? y[i + 1] : maximal;
        minimal = minimal > y[i + 1] ? y[i + 1] : minimal;
    }
}

void Num_Method::calc_tranc_error(QVector<double> own) {
    GTE[0] = 0;
    LTE[0] = 0;
    maximalLTE = 0;
    maximalGTE = 0;
    for (int i = 1; i < N + 1; i++){
        GTE[i] = abs(y[i] - own[i]);
        maximalGTE = maximalGTE < GTE[i] ? GTE[i] : maximalGTE;

        LTE[i] = abs(y[i] - local_formula(x0 + (X - x0) / N * (i - 1), own[i - 1]));
        maximalLTE = maximalLTE < LTE[i] ? LTE[i] : maximalLTE;
    }
}

void Num_Method::set_data (double x0, double y0, double X, int N){
    this->x0 = x0;
    this->y0 = y0;
    this->X = X;
    this->N = N;
    y.clear();
    y.resize(N + 1);
    GTE.clear();
    GTE.resize(N + 1);
    LTE.clear();
    LTE.resize(N + 1);
}
