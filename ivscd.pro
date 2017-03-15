#-------------------------------------------------
#
# Project created by QtCreator 2017-03-14T20:35:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ivscd
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cdmath.cpp

HEADERS  += mainwindow.h \
    ../../../../../pokus/mymath.h \
    cdmath.h

FORMS    += mainwindow.ui
