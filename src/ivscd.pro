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
    cdmath.cpp

HEADERS  += mainwindow.h \
    cdmath.h

FORMS    += mainwindow.ui

extra_clean.target = extra_clean
extra_clean.CONFIG = phony
extra_clean.commands += rm -rvf *.o moc_* ui_* build* ivscd tests/*.o tests/*.moc tests/test_cdmath doc
clean.depends += extra_clean

test.target = test
test.depends = tests/tests.pro tests/test_cdmath.cpp
test.commands += cd tests && qmake && make && ./test_cdmath

doc.target = doc
doc.depends = Doxyfile cdmath.h mainwindow.h cdmath.cpp mainwindow.cpp
doc.commands = doxygen

run.target = run
run.CONFIG = phony
run.depends = ivscd
run.commands = ./ivscd

QMAKE_EXTRA_TARGETS += clean extra_clean test doc run
