QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_credit.c \
    ../s21_smart_calc.c \
    ../s21_stack_func.c \
    credit_calc.cpp \
    grafic.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../s21_credit.h \
    ../s21_smart_calc.h \
    credit_calc.h \
    grafic.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit_calc.ui \
    grafic.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
