#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QVector>
#include "grafic.h"
#include "credit_calc.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../s21_smart_calc.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    grafic *graf;
    credit_calc *cred;
    QDoubleValidator m_doubleValidator;

private slots:
    void numbers();
    void left_bracket();
    void right_bracket();
    void dot();
    void clear();
    void number_x();
    void ariphmetic_operations();
    void functions();
    void result();
    void backspace();
    void credit();
};
#endif // MAINWINDOW_H
