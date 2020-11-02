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

    void getData();

private slots:
    void on_plot_Button_clicked();

private:
    Euler_Method euler;
    Improved_Euler_Method improved;
    Runge_Kutta_Method runge;
    Own_Exact_Solution own;
    Ui::MainWindow *ui;
    double step;
    void drawFirst();
    void drawSecond();
    void drawThird();
};

#endif // MAINWINDOW_H
