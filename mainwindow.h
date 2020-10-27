#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "grid.h"
#include "own_exact_solution.h"
#include "euler_method.h"
#include "improved_euler_method.h"
#include "runge_kutta_method.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawGraph(Euler_Method euler = *(new Euler_Method()),
                   Improved_Euler_Method improved = *(new Improved_Euler_Method()),
                   Runge_Kutta_Method runge = *(new Runge_Kutta_Method()),
                   Own_Exact_Solution own = *(new Own_Exact_Solution()));

    void recountPixels();
    void getData(Euler_Method euler, Improved_Euler_Method improved, Runge_Kutta_Method runge, Own_Exact_Solution own);

private slots:
    void on_plot_Button_clicked();

private:
    Ui::MainWindow *ui;
    double leftX, rightX;
    double leftY, rightY;
    int pictWidth, pictHeight;
    double step;
    double onePixelX,onePixelY;
    double Ox,Oy;
};

#endif // MAINWINDOW_H
