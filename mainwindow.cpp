#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "own_exact_solution.h"
#include "euler_method.h"
#include "improved_euler_method.h"
#include "runge_kutta_method.h"

#include <cmath>
#include <QDebug>
#include <float.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->is_Exact->setStyleSheet("QCheckBox { color: blue }");
    ui->is_Euler->setStyleSheet("QCheckBox { color: red }");
    ui->is_Improved->setStyleSheet("QCheckBox { color: green }");
    ui->is_Runge->setStyleSheet("QCheckBox { color: magenta }");

    ui->input_x0->setValidator(new QDoubleValidator(DBL_MIN, DBL_MAX, 5));
    ui->input_y0->setValidator(new QDoubleValidator(DBL_MIN, DBL_MAX, 5));
    ui->input_X->setValidator(new QDoubleValidator(DBL_MIN, DBL_MAX, 5));
    ui->input_N->setValidator(new QIntValidator(0, INT_MAX));

    step = 0.1;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::getData(){
    double x0 = ui->input_x0->text().toDouble();
    double y0 = ui->input_y0->text().toDouble();
    double X = ui->input_X->text().toDouble();
    double N = ui->input_N->text().toDouble();

    euler.set_data(x0, y0, X, N);
    improved.set_data(x0, y0, X, N);
    runge.set_data(x0, y0, X, N);
    own.set_data(x0, y0, X, N);

    euler.calculate_values();
    improved.calculate_values();
    runge.calculate_values();
    own.calculate_values();

    euler.calc_tranc_error(own.get_y());
    improved.calc_tranc_error(own.get_y());
    runge.calc_tranc_error(own.get_y());

    step = (X - x0) / N; // и шаг
}

void MainWindow::drawFirst(){
    if (!ui->is_Euler->isChecked() && !ui->is_Improved->isChecked() && !ui->is_Runge->isChecked() && !ui->is_Exact->isChecked()){
        ui->graph1->replot();
        return;
    }

    QVector<double> x(euler.get_N() + 1);
    double minimal = euler.get_y0(), maximal = euler.get_y0();

    for (int i = 0; i < euler.get_N() + 1; i++){
        x[i] = euler.get_x0() + step * i;
    }

    int counter = 0;
    if(ui->is_Euler->isChecked()) {
        ui->graph1->addGraph();

        ui->graph1->graph(counter)->setPen(QPen(Qt::red));
        ui->graph1->graph(counter)->setData(x, euler.get_y());

        maximal = maximal < euler.get_maximal() ? euler.get_maximal() : maximal;
        minimal = minimal > euler.get_minimal() ? euler.get_minimal() : minimal;

        counter++;
    }
    if(ui->is_Improved->isChecked()) {
        ui->graph1->addGraph();

        ui->graph1->graph(counter)->setPen(QPen(Qt::green));
        ui->graph1->graph(counter)->setData(x, improved.get_y());

        maximal = maximal < improved.get_maximal() ? improved.get_maximal() : maximal;
        minimal = minimal > improved.get_minimal() ? improved.get_minimal() : minimal;

        counter++;
    }
    if(ui->is_Runge->isChecked()) {
        ui->graph1->addGraph();

        ui->graph1->graph(counter)->setPen(QPen(Qt::magenta));
        ui->graph1->graph(counter)->setData(x, runge.get_y());

        maximal = maximal < runge.get_maximal() ? runge.get_maximal() : maximal;
        minimal = minimal > runge.get_minimal() ? runge.get_minimal() : minimal;

        counter++;
    }
    if(ui->is_Exact->isChecked()) {
        ui->graph1->addGraph();

        ui->graph1->graph(counter)->setPen(QPen(Qt::blue));
        ui->graph1->graph(counter)->setData(x, own.get_y());

        maximal = maximal < own.get_maximal() ? own.get_maximal() : maximal;
        minimal = minimal > own.get_minimal() ? own.get_minimal() : minimal;
    }

    ui->graph1->xAxis->setRange(own.get_x0(), own.get_X());
    ui->graph1->yAxis->setRange(minimal, maximal);
    ui->graph1->replot();
}

void MainWindow::drawSecond(){
    if (!ui->is_Euler->isChecked() && !ui->is_Improved->isChecked() && !ui->is_Runge->isChecked() && !ui->is_Exact->isChecked()){
        ui->graph2->replot();
        return;
    }

    QVector<double> x(euler.get_N() + 1);
    double maximal = 0;

    for (int i = 0; i < euler.get_N() + 1; i++){
        x[i] = euler.get_x0() + step * i;
    }

    int counter = 0;
    if(ui->is_Euler->isChecked()) {
        ui->graph2->addGraph();

        ui->graph2->graph(counter)->setPen(QPen(Qt::red));
        ui->graph2->graph(counter)->setData(x, euler.get_GTE());

        maximal = maximal < euler.get_maximalGTE() ? euler.get_maximalGTE() : maximal;
        counter++;
    }
    if(ui->is_Improved->isChecked()) {
        ui->graph2->addGraph();

        ui->graph2->graph(counter)->setPen(QPen(Qt::green));
        ui->graph2->graph(counter)->setData(x, improved.get_GTE());

        maximal = maximal < improved.get_maximalGTE() ? improved.get_maximalGTE() : maximal;
        counter++;
    }
    if(ui->is_Runge->isChecked()) {
        ui->graph2->addGraph();

        ui->graph2->graph(counter)->setPen(QPen(Qt::magenta));
        ui->graph2->graph(counter)->setData(x, runge.get_GTE());

        maximal = maximal < runge.get_maximalGTE() ? runge.get_maximalGTE() : maximal;
        counter++;
    }

    ui->graph2->xAxis->setRange(own.get_x0(), own.get_X());
    ui->graph2->yAxis->setRange(0, maximal);
    ui->graph2->replot();
}

void MainWindow::drawThird(){
    if (!ui->is_Euler->isChecked() && !ui->is_Improved->isChecked() && !ui->is_Runge->isChecked() && !ui->is_Exact->isChecked()){
        ui->graph3->replot();
        return;
    }

    QVector<double> x(euler.get_N() + 1);
    double maximal = 0;

    for (int i = 0; i < euler.get_N() + 1; i++){
        x[i] = euler.get_x0() + step * i;
    }

    int counter = 0;
    if(ui->is_Euler->isChecked()) {
        ui->graph3->addGraph();

        ui->graph3->graph(counter)->setPen(QPen(Qt::red));
        ui->graph3->graph(counter)->setData(x, euler.get_LTE());

        maximal = maximal < euler.get_maximalLTE() ? euler.get_maximalLTE() : maximal;
        counter++;
    }
    if(ui->is_Improved->isChecked()) {
        ui->graph3->addGraph();

        ui->graph3->graph(counter)->setPen(QPen(Qt::green));
        ui->graph3->graph(counter)->setData(x, improved.get_LTE());

        maximal = maximal < improved.get_maximalLTE() ? improved.get_maximalLTE() : maximal;
        counter++;
    }
    if(ui->is_Runge->isChecked()) {
        ui->graph3->addGraph();

        ui->graph3->graph(counter)->setPen(QPen(Qt::magenta));
        ui->graph3->graph(counter)->setData(x, runge.get_LTE());

        maximal = maximal < runge.get_maximalLTE() ? runge.get_maximalLTE() : maximal;
        counter++;
    }

    ui->graph3->xAxis->setRange(own.get_x0(), own.get_X());
    ui->graph3->yAxis->setRange(0, maximal);
    ui->graph3->replot();
}

void MainWindow::on_plot_Button_clicked(){
    ui->graph1->clearGraphs();
    ui->graph2->clearGraphs();
    ui->graph3->clearGraphs();

    getData();

    drawFirst();
    drawSecond();
    drawThird();
}
