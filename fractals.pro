#-------------------------------------------------
#
# Project created by QtCreator 2012-09-30T15:39:51
#
#-------------------------------------------------

QT       += core gui
CONFIG += qt debug

TARGET = fractals
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    region.cpp \
    regionmanager.cpp \
    qcustomplot.cpp \
    fractalworker.cpp

HEADERS  += mainwindow.h \
    math_functions.h \
    region.h \
    regionmanager.h \
    qcustomplot.h \
    fractalworker.h

FORMS    += mainwindow.ui
