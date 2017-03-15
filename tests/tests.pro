#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T10:49:21
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = test_cdmath
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ..

SOURCES += test_cdmath.cpp \
        ../cdmath.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
