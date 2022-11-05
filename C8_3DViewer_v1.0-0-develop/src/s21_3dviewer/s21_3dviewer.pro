QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT +=  widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../backend/matrix_lib/s21_matrix.c \
    ../backend/s21_parsing_object.c \
    ../QtGifImage-master/src/gifimage/qgifimage.h \
    mainwindow.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    ../backend/matrix_lib/s21_matrix.h \
    ../backend/s21_parsing_object.h \
    ../QtGifImage-master/src/gifimage/qgifimage.h \
    mainwindow.h \
    widget.h

FORMS += \
    mainwindow.ui \
    widget.ui
include (../QtGifImage-master/src/gifimage/qtgifimage.pri)
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Makefile
