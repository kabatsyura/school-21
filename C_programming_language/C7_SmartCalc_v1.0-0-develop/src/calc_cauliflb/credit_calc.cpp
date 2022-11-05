#include "credit_calc.h"
#include "ui_credit_calc.h"
#include "mainwindow.h"
#include <QMessageBox>

credit_calc::credit_calc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::credit_calc)
{
    ui->setupUi(this);
}

credit_calc::~credit_calc()
{
    delete ui;
}

void credit_calc::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    double sum = ui->lineEdit->text().toDouble();
    int data = ui->lineEdit_2->text().toInt();
    double procent = ui->lineEdit_3->text().toDouble();


    int type = ui->radioButton->isChecked() ? 1 : 2;
    data = (ui->comboBox->currentIndex() == 0) ? data : data * 12;

    double mutualpay = 0.0, overpay = 0.0, every_month[data];

   if (sum <= 0 || data <= 0 || procent <= 0) {
       QMessageBox::warning(this, "Error", "Неправильные входные данные");
    } else {
          credit(type, sum, data, procent, &mutualpay, &overpay, every_month);
        ui->lineEdit_6->setText(QString::number(overpay, 'f', 2));
        ui->lineEdit_4->setText(QString::number(mutualpay, 'f', 2));
        ui->textEdit->verticalScrollBar();
        for (int i = 1, j = 0; i <= data; i++, j++) {
            ui->textEdit->insertPlainText("Месяц " + QString::number(i) + ": " + QString::number(every_month[j], 'f', 2) + "\n");
            ui->textEdit->textCursor().movePosition(QTextCursor::Start);
        }
   }
}
