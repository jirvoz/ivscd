#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cdmath.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    resetInput(false),
    memory(0)
{
    ui->setupUi(this);  



    QPushButton* numLst[] = {ui->b0, ui->b1, ui->b2, ui->b3, ui->b4, ui->b5, ui->b6, ui->b7, ui->b8, ui->b9 };

    for(auto i:numLst){

        connect(i, SIGNAL(clicked()), this, SLOT(addNum()));

    }

    QPushButton* binOpLst[] = {ui->bAdd, ui->bDiv, ui->bPower, ui->bSub, ui->bTimes,  };

    for(auto i:binOpLst){

        connect(i, SIGNAL(clicked()), this, SLOT(addBinOp()));

    }

    connect(ui->bEquals, SIGNAL(clicked()), this, SLOT(equalsPressed()));

    connect(ui->bDot, SIGNAL(clicked()), this, SLOT(addDot()));

    connect(ui->bSign, SIGNAL(clicked()), this, SLOT(toggleSign()));

    connect(ui->bBack, SIGNAL(clicked()), this, SLOT(backSpace()));

    connect(ui->bClear, SIGNAL(clicked()), this, SLOT(clear()));

    connect(ui->bAllClear, SIGNAL(clicked()), this, SLOT(clearAll()));


    //qDebug() << QString("- SD").right(4 - 2);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addNum(){

    QString num = qobject_cast<QPushButton*>(sender())->text();
    QString str = ui->resultLabel->text();

    if(resetInput){

        ui->inputLabel->setText(QString(""));

        resetInput = false;QString str = ui->resultLabel->text();
    }

    if(str == QString("0") || resetResult){
        str = num;
        resetResult = false;
    }
    else{
        str += num;
    }

    ui->resultLabel->setText(str);

    binOp = false;

}

void MainWindow::addBinOp(){

    if(resetInput){

        ui->inputLabel->setText(QString(""));

        resetInput = false;
    }


    QString str = ui->inputLabel->text();

    if(binOp){
        str = str.left(str.length() - 2) + qobject_cast<QPushButton*>(sender())->text() + " ";
    }
    else{
        str += ui->resultLabel->text() + " " + qobject_cast<QPushButton*>(sender())->text() + " ";
    }

    ui->inputLabel->setText(str);

    resetResult = true;
    binOp = true;

}

void MainWindow::equalsPressed(){


    QString str = ui->inputLabel->text() + ui->resultLabel->text();

    ui->inputLabel->setText(str);

    ui->resultLabel->setText(QString::number(math.evaluate(str)));


    resetResult = true;
    resetInput = true;
    binOp = false;
}

void MainWindow::addDot(){

    QString str = ui->resultLabel->text();
    if (str.right(1) != QString(".")){
        ui->resultLabel->setText(ui->resultLabel->text() + ".");
}

}

void MainWindow::toggleSign(){

    QString str = ui->resultLabel->text();
    if(str != "0" && str != "0."){
        if(str.left(1) == QString("-")){
            str = str.right(str.length() - 2);

        }
        else{
            str = "- " + str;
        }

        ui->resultLabel->setText(str);

    }
}

void MainWindow::backSpace(){

    QString str = ui->resultLabel->text();
    str = str.left(str.length() - 1);
    if(str.length() == 0){
        str = "0";
    }
    ui->resultLabel->setText(str);
}

void MainWindow::clear(){
   ui->resultLabel->setText(QString("0"));
}

void MainWindow::clearAll(){
   ui->resultLabel->setText(QString("0"));
   memory = 0;
   ui->inputLabel->setText(QString(""));

}
