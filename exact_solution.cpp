#include "exact_solution.h"

QVector<double> Exact_Solution::get_y() {
    return y;
}

double Exact_Solution::get_minimal(){
    return minimal;
}

double Exact_Solution::get_maximal(){
    return maximal;
}

void Exact_Solution::set_data (double x0, double y0, double X, int N){
    this->x0 = x0;
    this->y0 = y0;
    this->X = X;
    this->N = N;
    y.clear();
    y.resize(N + 1);
}
