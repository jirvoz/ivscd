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

#clean
extra_clean.target = extra_clean
extra_clean.CONFIG = phony
extra_clean.commands += rm -rvf *.o moc_* ui_* build* ivscd tests/*.o tests/*.moc tests/test_cdmath doc ivscd_1.0-1.deb
clean.depends += extra_clean

#test
test.target = test
test.depends = tests/tests.pro tests/test_cdmath.cpp
test.commands = cd tests && qmake && make && ./test_cdmath

#doc
doc.target = doc
doc.depends = Doxyfile cdmath.h mainwindow.h cdmath.cpp mainwindow.cpp
doc.commands = doxygen

#run
run.target = run
run.CONFIG = phony
run.depends = ivscd
run.commands = ./ivscd

#package
ivsdeb.target = ivscd_1.0-1.deb
ivsdeb.depends = ivscd
ivsdeb.commands = mkdir -p ivscd_1.0-1/usr/local/bin && cp ivscd ivscd_1.0-1/usr/local/bin && dpkg-deb --build ivscd_1.0-1
#alias for deb package ivscd_1.0-1.deb
deb.target = deb
deb.CONFIG = phony
deb.depends = ivscd_1.0-1.deb

QMAKE_EXTRA_TARGETS += clean extra_clean test doc run ivsdeb deb

#install
target.path = /usr/local/bin/
INSTALLS += target
