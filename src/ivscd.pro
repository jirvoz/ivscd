#-------------------------------------------------
#
# Project created by QtCreator 2017-03-14T20:35:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ivscd
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    cdmath.cpp \
    ../../../2/ivscd -sdeviation (copy)/sdeviation.cpp

HEADERS  += mainwindow.h \
    cdmath.h

FORMS    += mainwindow.ui

doc.target = doc
doc.depends = Doxyfile cdmath.h mainwindow.h cdmath.cpp mainwindow.cpp
doc.commands = doxygen

QMAKE_EXTRA_TARGETS += doc
