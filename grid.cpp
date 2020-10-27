#include "grid.h"

Grid::Grid()
{
    x0 = 1;
    y0 = 1;
    X = 6;
    N = 600;
}

double Grid::get_x0() {
    return this->x0;
}
double Grid::get_y0() {
    return this->y0;
}
double Grid::get_X() {
    return this->X;
}
int Grid::get_N() {
    return this->N;
}

void Grid::set_data (double x0, double y0, double X, double N){
    this->x0 = x0;
    this->y0 = y0;
    this->X = X;
    this->N = N;
}
