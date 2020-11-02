#ifndef INIT_H
#define INIT_H

class Grid{
protected:
    double x0;
    double y0;
    double X;
    int N;

public:
    Grid();
    double get_x0();
    double get_y0();
    double get_X();
    int get_N();

    virtual void set_data(double x0 = 1, double y0 = 1, double X = 6, int N = 600) = 0;
};

#endif // INIT_H
