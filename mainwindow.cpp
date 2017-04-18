#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cdmath.h"
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    resetInput(false),
    resetResult(false),
    binOp(false),
    memory(0),
    lParenCount(0)
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

    connect(ui->bPi, SIGNAL(clicked()), this, SLOT(setPi()));

    connect(ui->bEuler, SIGNAL(clicked()), this, SLOT(setEuler()));

    connect(ui->bMR, SIGNAL(clicked()), this, SLOT(memoryRead()));

    connect(ui->bMC, SIGNAL(clicked()), this, SLOT(memoryClear()));

    connect(ui->bMS, SIGNAL(clicked()), this, SLOT(memorySet()));

    connect(ui->bMadd, SIGNAL(clicked()), this, SLOT(memoryAdd()));

    connect(ui->bMsub, SIGNAL(clicked()), this, SLOT(memorySub()));

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

void MainWindow::keyPressEvent(QKeyEvent *event ){

    if(event->key() == Qt::Key_Return){
        ui->bEquals->animateClick();
    }

    if(event->key() == Qt::Key_Backspace){
        ui->bBack->animateClick();
    }

    if(event->key() == Qt::Key_C){
        ui->bClear->animateClick();
    }
    if(event->key() == Qt::Key_0 ){
        ui->b0->animateClick();
    }
    if(event->key() == Qt::Key_1 ){
        ui->b1->animateClick();
    }
    if(event->key() == Qt::Key_2 ){
        ui->b2->animateClick();
    }
    if(event->key() == Qt::Key_3 ){
        ui->b3->animateClick();
    }
    if(event->key() == Qt::Key_4 ){
        ui->b4->animateClick();
    }
    if(event->key() == Qt::Key_5 ){
        ui->b5->animateClick();
    }
    if(event->key() == Qt::Key_6 ){
        ui->b6->animateClick();
    }
    if(event->key() == Qt::Key_7 ){
        ui->b7->animateClick();
    }
    if(event->key() == Qt::Key_8 ){
        ui->b8->animateClick();
    }
    if(event->key() == Qt::Key_9 ){
        ui->b9->animateClick();
    }
    if(event->key() == Qt::Key_Period ){
        ui->bDot->animateClick();
    }
    if(event->key() == Qt::Key_Slash ){
        ui->bDiv->animateClick();
    }
    if(event->key() == Qt::Key_Asterisk ){
        ui->bTimes->animateClick();
    }
    if(event->key() == Qt::Key_Plus ){
        ui->bAdd->animateClick();
    }
    if(event->key() == Qt::Key_Minus ){
        ui->bSub->animateClick();
    }
    if(event->key() == Qt::Key_Percent ){
        ui->bMod->animateClick();
    }
    if(event->key() == Qt::Key_E ){
        ui->bEuler->animateClick();
    }
    if(event->key() == Qt::Key_P ){
        ui->bPi->animateClick();
    }
    if(event->key() == Qt::Key_ParenRight ){
        ui->bParenR->animateClick();
    }
    if(event->key() == Qt::Key_ParenLeft ){
        ui->bParenL->animateClick();
    }
    if(event->key() == Qt::Key_Exclam ){
        ui->bFactorial->animateClick();
    }
    if(event->key() == Qt::Key_S){
        ui->bSign->animateClick();
    }
    if(event->key() == 94){ // ^
        ui->bPower->animateClick();
    }
    if(event->key() == Qt::Key_A){
        ui->bAllClear->animateClick();
    }
}

void MainWindow::setPi(){
    ui->resultLabel->setText(QString::number(M_PI, 'g', 15));
}

void MainWindow::setEuler(){
    ui->resultLabel->setText(QString::number(M_E, 'g', 15));
}

void MainWindow::memorySet(){

    memory = ui->resultLabel->text().toDouble();
}

void MainWindow::memoryClear(){

    memory = 0;
}

void MainWindow::memoryRead(){

    ui->resultLabel->setText(QString::number(memory));
}

void MainWindow::memoryAdd(){

    memory += ui->resultLabel->text().toDouble();
}

void MainWindow::memorySub(){

    memory -= ui->resultLabel->text().toDouble();
}
