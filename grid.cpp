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
