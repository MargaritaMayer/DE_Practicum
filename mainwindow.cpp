#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "own_exact_solution.h"
#include "euler_method.h"
#include "improved_euler_method.h"
#include "runge_kutta_method.h"

#include <cmath>
#include <QDebug>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); // означает, что будем использовать форму
    pictHeight = 370; // задаем высоту картинки
    pictWidth = 540; // и её ширину
    step = 0.1; // задаем начальный шаг
    leftX = -100; rightX = 100; // и начальные значения границ
    leftY = -100; rightY = 100;
    drawGraph(); // сразу же отрисовываем пустой график
}

MainWindow::~MainWindow()
{
    delete ui; // стандартный деструктор
}

void MainWindow::recountPixels()
{
    onePixelX = 540.0/(rightX-leftX);
    onePixelY = 370.0/(rightY-leftY);
    Ox = fabs(leftX); Oy = rightY;
}

void MainWindow::getData(Euler_Method euler, Improved_Euler_Method improved, Runge_Kutta_Method runge, Own_Exact_Solution own){
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

    double minimal = y0, maximal = y0;
    for (int i = 0; i < N; i++) {
        minimal = minimal > euler[i] ? euler[i] : minimal;
        minimal = minimal > improved[i] ? improved[i] : minimal;
        minimal = minimal > runge[i] ? runge[i] : minimal;

        maximal = maximal < euler[i] ? euler[i] : maximal;
        maximal = maximal < improved[i] ? improved[i] : maximal;
        maximal = maximal < runge[i] ? runge[i] : maximal;
    }

    leftX = x0; // узнаем границы
    rightX = X;
    leftY = minimal;
    rightY = maximal;
    step = (X - x0) / N; // и шаг
}


//void MainWindow::drawGraph(Euler_Method euler, Improved_Euler_Method improved, Runge_Kutta_Method runge, Own_Exact_Solution own){}
void MainWindow::drawGraph(Euler_Method euler, Improved_Euler_Method improved, Runge_Kutta_Method runge, Own_Exact_Solution own) {



    /*    QPixmap graph(540,370); // создаем саму картинку
    QPainter paint; // и пэинтер
    paint.begin(&graph); // запускаем отрисовку
    paint.eraseRect(0, 0, 540, 370); // очищаем рисунок

    paint.drawLine(10, 10, 540, 370);
    paint.drawLine(onePixelX, onePixelY, onePixelX * 2, onePixelY * 3);

    if(ui->is_Exact->isChecked()) {
        paint.setPen(QPen(Qt::blue,1,Qt::SolidLine));
        for (int i = 0; i < own.get_N() - 1; i++){
            paint.drawLine(step * i * onePixelX, step * (own[i] - own.get_y0()) * onePixelY, step * (i + 1) * onePixelX, step * (own[i + 1] - own.get_y0()) * onePixelY);
        }
    }
    if(ui->is_Euler->isChecked()) {
        paint.setPen(QPen(Qt::green,1,Qt::SolidLine));
        for (int i = 0; i < own.get_N() - 1; i++){
            paint.drawLine(step * i * onePixelX, step * euler[i] * onePixelY, step * (i + 1) * onePixelX, step * euler[i + 1] * onePixelY);
        }
    }
    if(ui->is_Improved->isChecked()) {
        paint.setPen(QPen(Qt::red,1,Qt::SolidLine));
        for (int i = 0; i < own.get_N() - 1; i++){
            paint.drawLine(step * i * onePixelX, step * improved[i] * onePixelY, step * (i + 1) * onePixelX, step * improved[i + 1] * onePixelY);
        }
    }
    if(ui->is_Runge->isChecked()) {
        paint.setPen(QPen(Qt::darkMagenta,1,Qt::SolidLine));
        for (int i = 0; i < own.get_N() - 1; i++){
            paint.drawLine(step * i * onePixelX, step * runge[i] * onePixelY, step * (i + 1) * onePixelX, step * runge[i + 1] * onePixelY);
        }
    }
    paint.end(); // заканчиваем рисование
    ui->output_graph->setPixmap(graph); // и помещаем рисунок на форму
    return;


    paint.drawLine(Ox * onePixelX, 0, Ox * onePixelX, pictHeight); // и рисуем координатные оси
    paint.drawLine(0, Oy*onePixelY, pictWidth, Oy*onePixelY);

    paint.setPen(QPen(Qt::black,3)); // устанавливаем цвет и толщину "пера"
    for(double i = leftX; i <= rightX; i += 10.0) // рисуем черточки на координатой оси
        paint.drawPoint((i + Ox) * onePixelX, Oy * onePixelY);
    for(double i = leftY; i <= rightY; i += 10.0)
        paint.drawPoint(Ox * onePixelX, (i + Oy) * onePixelY);

    paint.setPen(QPen(Qt::green,1,Qt::SolidLine)); // снова задаем цвет и тип линии
    paint.setRenderHint(QPainter::Antialiasing, true); // задаем параметры рендеринга
    QPainterPath p[4]; // QPainterPath означаем, что мы вначале занесем все необходимые точки, а затем соединим их
    bool first[4] = {1,1,1,1}; // узнаем первая ли точка, или надо сдвигаться

    for(int i = 0; i<= euler.get_N(); i++) {
        if(first[0]) {
            p[0].moveTo((Ox + step * i)*onePixelX,(euler[i] + Oy)*onePixelY);
            first[0] = false;
        }
        else
            p[0].lineTo((Ox + step * i)*onePixelX,(euler[i] + Oy)*onePixelY);

        if(first[1]) {
            p[1].moveTo((Ox + step * i)*onePixelX,(improved[i] + Oy)*onePixelY);
            first[1] = false;
        }
        else
            p[1].lineTo((Ox + step * i)*onePixelX,(improved[i] + Oy)*onePixelY);

        if(first[2]) {
            p[2].moveTo((Ox + step * i)*onePixelX,(runge[i] + Oy)*onePixelY);
            first[2] = false;
        }
        else
            p[2].lineTo((Ox + step * i)*onePixelX,(runge[i] + Oy)*onePixelY);

        if(first[3]) {
            p[3].moveTo((Ox + step * i)*onePixelX,(own[i] + Oy)*onePixelY);
            first[3] = false;
        }
        else
            p[3].lineTo((Ox + step * i)*onePixelX,(own[i] + Oy)*onePixelY);
    }

    // проверяем, если в CheckBox отмечено, что график надо отрисовывать -- задаем нужный цвет и отрисовываем с помощью функции drawPath()
    if(ui->is_Exact->isChecked()) {
        paint.setPen(QPen(Qt::blue,1,Qt::SolidLine));
        paint.drawPath(p[3]);
    }
    if(ui->is_Euler->isChecked()) {
        paint.setPen(QPen(Qt::green,1,Qt::SolidLine));
        paint.drawPath(p[0]);
    }
    if(ui->is_Improved->isChecked()) {
        paint.setPen(QPen(Qt::red,1,Qt::SolidLine));
        paint.drawPath(p[1]);
    }
    if(ui->is_Runge->isChecked()) {
        paint.setPen(QPen(Qt::darkMagenta,1,Qt::SolidLine));
        paint.drawPath(p[2]);
    }
    paint.end(); // заканчиваем рисование
    ui->output_graph->setPixmap(graph); // и помещаем рисунок на форму
    return;
    */
}

void MainWindow::on_plot_Button_clicked(){
    ui->

    /*    Euler_Method euler;
    Improved_Euler_Method improved;
    Runge_Kutta_Method runge;
    Own_Exact_Solution own;

    getData(euler, improved, runge, own);
    recountPixels();
    drawGraph(euler, improved, runge, own);*/
}
