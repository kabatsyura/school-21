#ifndef GRAFIC_H
#define GRAFIC_H

#include <QDialog>
#include <QVector>
#include <QTimer>

extern "C" {
#include "../s21_smart_calc.h"
}

namespace Ui {
class grafic;
}

class grafic : public QDialog
{
    Q_OBJECT

public:
    explicit grafic(QWidget *parent = nullptr);
    ~grafic();

public slots:
    void MakeGraf(QString str);

private:
    Ui::grafic *ui;
    double xBegin, xEnd, h, X;

    QVector<double> x, y;
};

#endif // GRAFIC_H
