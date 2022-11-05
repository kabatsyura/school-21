#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <QDialog>

#ifdef __cplusplus
extern "C" {
#endif
#include "../s21_credit.h"
#ifdef __cplusplus
}
#endif

namespace Ui {
class credit_calc;
}

class credit_calc : public QDialog
{
    Q_OBJECT

public:
    explicit credit_calc(QWidget *parent = nullptr);
    ~credit_calc();

public slots:
    void on_pushButton_2_clicked();

private:
    Ui::credit_calc *ui;
};

#endif // CREDIT_CALC_H

