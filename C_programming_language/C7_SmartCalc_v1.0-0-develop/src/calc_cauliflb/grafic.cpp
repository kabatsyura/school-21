#include "grafic.h"
#include "ui_grafic.h"
#include "mainwindow.h"

grafic::grafic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::grafic)
{
    ui->setupUi(this);


}

grafic::~grafic()
{
    delete ui;
}

void grafic::MakeGraf(QString str_test) {
    QString str_buf = str_test;
    h = 0.1;
    xBegin = 0;
    xEnd = 10;
    double yaxis_minus = 0;
    double yaxis_plus = 0;

    for(X = xBegin; X <= xEnd; X += h)
    {
        str_buf.replace("X", QString::number(X));
        QByteArray test = str_buf.toLocal8Bit();
        char *str = test.data();
        double res = 0.0;
        int error = input_output(str, 0.0, &res);

        if(error)
        {
            EXIT_FAILURE;
        }
        else
        {
            x.push_back(X);
            y.push_back(res);
            if (res < 0) {
                if(res < yaxis_minus)
                yaxis_minus = res;
            } else {
                if(yaxis_minus > 0)
                yaxis_minus = res;
                if(res > yaxis_plus)
                yaxis_plus = res;
            }
        }
        str_buf = str_test;
    }

    ui->widget->xAxis->setRange(0,10);
    ui->widget->yAxis->setRange(round(yaxis_minus), round(yaxis_plus));

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();
}
