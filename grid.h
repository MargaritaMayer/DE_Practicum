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

    void set_data (double x0, double y0, double X, double N);
};

#endif // INIT_H
