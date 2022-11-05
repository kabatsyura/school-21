#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grafic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_doubleValidator(-10000000, 10000000, 15, this)
{
    ui->setupUi(this);

    m_doubleValidator.setNotation(QDoubleValidator::StandardNotation);


    /*соединяю кнопки с методами*/
    /* numbers */
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(numbers()));

    /* x */
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(number_x()));

    /* bracket */

    connect(ui->pushButton_rightBracket, SIGNAL(clicked()), this, SLOT(right_bracket()));
    connect(ui->pushButton_leftBracket, SIGNAL(clicked()), this, SLOT(left_bracket()));

    /* dot */
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dot()));

    /* clear */
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clear()));

    /* aripthmetics operators */
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(ariphmetic_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(ariphmetic_operations()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(ariphmetic_operations()));
    connect(ui->pushButton_devision, SIGNAL(clicked()), this, SLOT(ariphmetic_operations()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(ariphmetic_operations()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(ariphmetic_operations()));

    /* functions */

    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));

    /* equal */
    connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(result()));

    /* backspace */
    connect(ui->pushButton_backspace, SIGNAL(clicked()), this, SLOT(backspace()));

    /*credit calculator*/
    connect(ui->pushButton_credit, SIGNAL(clicked()), this, SLOT(credit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numbers() {
    QPushButton *button = (QPushButton *) sender();


    if (ui->screen->text().endsWith("0") && ui->screen->text().size() == 1) {
        ui->screen->setText(button->text());
    } else {
        if (ui->screen->text().endsWith("X") != 1 && button->text() !="X") {
          ui->screen->setText(ui->screen->text() + button->text());
        } else {
          ui->screen->setText("");
        }
    }
}

void MainWindow::left_bracket() {
    QPushButton *button = (QPushButton *) sender();

    int error = 1;

    if (ui->screen->text().endsWith(")") ||
        ui->screen->text().endsWith("X") ||
        ui->screen->text().endsWith("1") ||
        ui->screen->text().endsWith("2") ||
        ui->screen->text().endsWith("3") ||
        ui->screen->text().endsWith("4") ||
        ui->screen->text().endsWith("5") ||
        ui->screen->text().endsWith("6") ||
        ui->screen->text().endsWith("7") ||
        ui->screen->text().endsWith("8") ||
        ui->screen->text().endsWith("9")) {
            error = 0;
    }

    if (error == 1) {
        if (ui->screen->text().endsWith("0") && ui->screen->text().size() == 1) {
            ui->screen->setText(button->text());
        } else {
            ui->screen->setText(ui->screen->text() + button->text());
        }
    }
}

void MainWindow::right_bracket() {
    QPushButton *button = (QPushButton *) sender();

    int error = 1;

    if (ui->screen->text().endsWith("(") ||
        (ui->screen->text().endsWith("0") && ui->screen->text().size() == 1) ||
         ui->screen->text().size() == 0) {
            error = 0;
    }

    if (error == 1) {
        if (button->text() == ")") {
            ui->screen->setText(ui->screen->text() + button->text());
         }
    }
}

void MainWindow::dot() {
    QPushButton *button = (QPushButton *) sender();

    int error = 1;

    if (ui->screen->text().endsWith("(") ||
        ui->screen->text().endsWith(")") ||
        ui->screen->text().endsWith("+") ||
        ui->screen->text().endsWith("-") ||
        ui->screen->text().endsWith("*") ||
        ui->screen->text().endsWith("/") ||
        ui->screen->text().endsWith("^") ||
        ui->screen->text().endsWith("mod") ||
        ui->screen->text().endsWith(".") ||
        ui->screen->text().endsWith("X") ||
         ui->screen->text().size() == 0) {
            error = 0;
    }

    if (error == 1) {
        if (button->text() == ".") {
            ui->screen->setText(ui->screen->text() + button->text());
         }
    }
}

void MainWindow::clear() {
    ui->screen->setText("0");
}

void MainWindow::number_x() {
    QPushButton *button = (QPushButton *) sender();

    if ((ui->screen->text().endsWith("0") && ui->screen->text().size() == 1) ||
         ui->screen->text().size() == 0) {
        ui->screen->setText(button->text());
    } else if (ui->screen->text().endsWith("x") ||
               ui->screen->text().endsWith("+") ||
               ui->screen->text().endsWith("-") ||
               ui->screen->text().endsWith("*") ||
               ui->screen->text().endsWith("/") ||
               ui->screen->text().endsWith("^") ||
               ui->screen->text().endsWith("(") ||
               ui->screen->text().endsWith("mod")) {
                   ui->screen->setText(ui->screen->text() + button->text());
    }
}

void MainWindow::ariphmetic_operations() {
    QPushButton *button = (QPushButton *) sender();

    int error = 1;

    if (ui->screen->text().endsWith("+") ||
        ui->screen->text().endsWith("-") ||
        ui->screen->text().endsWith("*") ||
        ui->screen->text().endsWith("/") ||
        ui->screen->text().endsWith("^") ||
        ui->screen->text().endsWith("mod") ||
        ui->screen->text().size() == 0) {
            error = 0;
    }

    if (error == 1) {
        if (button->text() == "+" || button->text() == "-" ||
            button->text() == "*" || button->text() == "/" ||
            button->text() == "^" || button->text() == "mod") {
                ui->screen->setText(ui->screen->text() + button->text());
        }
    }
}

void MainWindow::result() {
    // QPushButton *button = (QPushButton *) sender();

    double result = 0.0;

    if (ui->screen->text().contains("X")) {
        graf = new grafic(this);
        graf->show();
        graf->MakeGraf(ui->screen->text());
        for (int i = 0; i <= 10; i++) {

        }
    } else {
        QByteArray ba = ui->screen->text().toLocal8Bit();
        char *c_str2 = ba.data();
        if (input_output(c_str2, 0, &result) == 0)
            ui->screen->setText(QString::number(result, 'g', 17));
        else {
            ui->screen->setText("В выражении ошибка. Попробуйте ввести ещё раз!");
        }
    }
}

void MainWindow::functions() {
    QPushButton * button = (QPushButton *) sender();

    int error = 1;

    if (ui->screen->text().endsWith(")") ||
        ui->screen->text().endsWith("X") ||
        (ui->screen->text().endsWith("0") && ui->screen->text().size() > 1) ||
        ui->screen->text().endsWith("1") ||
        ui->screen->text().endsWith("2") ||
        ui->screen->text().endsWith("3") ||
        ui->screen->text().endsWith("4") ||
        ui->screen->text().endsWith("5") ||
        ui->screen->text().endsWith("6") ||
        ui->screen->text().endsWith("7") ||
        ui->screen->text().endsWith("8") ||
        ui->screen->text().endsWith("9")) {
            error = 0;
    }

    if (error == 1) {
        if ((ui->screen->text().endsWith("0") && ui->screen->text().size() == 1) ||
             ui->screen->text().size() == 0) {
            ui->screen->setText(button->text());
        } else if (button->text() == "cos(" || button->text() == "sin(" ||
            button->text() == "tan(" || button->text() == "acos("||
            button->text() == "asin(" || button->text() == "atan(" ||
            button->text() == "sqrt(" || button->text() == "ln(" ||
            button->text() == "log(") {
                ui->screen->setText(ui->screen->text() + button->text());
        }
    }
}

void MainWindow::backspace() {
    QString text = ui->screen->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "";
    }
    ui->screen->setText(text);
}

void MainWindow::credit() {
    cred = new credit_calc(this);
    cred->show();
    cred->on_pushButton_2_clicked();
}
