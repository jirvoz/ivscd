#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cdmath.h"
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  



    QPushButton* numLst[] = {ui->b0, ui->b1, ui->b2, ui->b3, ui->b4, ui->b5, ui->b6, ui->b7, ui->b8, ui->b9 };

    for(auto i:numLst){

        connect(i, SIGNAL(clicked()), this, SLOT(addNum()));

    }

    QPushButton* binOpLst[] = {ui->bAdd, ui->bDiv, ui->bPower, ui->bSub, ui->bTimes, ui->bMod };

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

    connect(ui->bParenL, SIGNAL(clicked()), this, SLOT(addLparen()));

    connect(ui->bParenR, SIGNAL(clicked()), this, SLOT(addRparen()));

    connect(ui->bReciproc, SIGNAL(clicked()), this, SLOT(reciproc()));


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

        resetInput = false;
    }
    if(str == QString("-")){
        str += " ";
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
    eqPressed = false;

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
    else if(rParen){
        str += " " + qobject_cast<QPushButton*>(sender())->text() + " ";
    }
    else{

        if(ui->resultLabel->text().left(1) == QString("-") && ui->inputLabel->text().length() > 0 && lParen == false ){
            str += "( " + ui->resultLabel->text() + " ) " + qobject_cast<QPushButton*>(sender())->text() + " ";
        }
        else{
            if(lParen){
                str += QString(" ");
            }

            str += ui->resultLabel->text() + " " + qobject_cast<QPushButton*>(sender())->text() + " ";
        }
    }

    ui->inputLabel->setText(str);

    resetResult = true;
    binOp = true;
    lParen = false;
    rParen = false;
    eqPressed = false;

}

void MainWindow::equalsPressed(){
    if(!eqPressed){
        if(resetInput){
            ui->inputLabel->setText(QString(""));

            resetInput = false;
        }
        QString str;
        if(rParen){
             str = ui->inputLabel->text();
        }
        else{
             str = ui->inputLabel->text() + ui->resultLabel->text();
        }
        if(lParenCount > 0){
            if(!rParen){
                str += " ";
            }
            for(int i = 0; i < lParenCount; i++){
                str += ")";
            }
        }

        ui->inputLabel->setText(str);

        ui->resultLabel->setText(QString::number(math.evaluate(str)));
    }

    resetResult = true;
    resetInput = true;
    binOp = false;
    lParen = false;
    rParen = false;
    eqPressed = true;
    lParenCount = 0;
    ui->bParenR->setEnabled(false);
}

void MainWindow::addDot(){

    QString str = ui->resultLabel->text();

    if (str.right(1) != QString(".")){
        if(str == "-"){
            str += " 0";
        }
        else if(str == "- "){
            str += "0";
        }

        ui->resultLabel->setText(str + ".");
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
        eqPressed = false;
    }
}

void MainWindow::backSpace(){

    if(resetResult){
        ui->resultLabel->setText("");
    }

    QString str = ui->resultLabel->text();
    str = str.left(str.length() - 1);
    if(str.length() == 0){
        str = "0";
    }
    ui->resultLabel->setText(str);

    eqPressed = false;
}

void MainWindow::clear(){

    if(resetInput){
        ui->inputLabel->setText("");
    }

   ui->resultLabel->setText(QString("0"));
}

void MainWindow::clearAll(){
   ui->resultLabel->setText(QString("0"));
   memory = 0;
   ui->inputLabel->setText(QString(""));
   lParen = false;
   binOp = false;
   resetInput = false;
   resetResult = false;
   rParen = false;
   eqPressed = false;
   lParenCount = 0;
   ui->bParenR->setEnabled(false);
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
    eqPressed = false;
}

void MainWindow::setEuler(){
    ui->resultLabel->setText(QString::number(M_E, 'g', 15));
    eqPressed = false;
}

void MainWindow::memorySet(){

    memory = ui->resultLabel->text().toDouble();
    resetResult = true;
}

void MainWindow::memoryClear(){

    memory = 0;
}

void MainWindow::memoryRead(){

    ui->resultLabel->setText(QString::number(memory));
    resetResult = true;
}

void MainWindow::memoryAdd(){

    memory += ui->resultLabel->text().toDouble();
    resetResult = true;
}

void MainWindow::memorySub(){

    memory -= ui->resultLabel->text().toDouble();
    resetResult = true;
}

void MainWindow::addLparen(){

    ui->bParenR->setEnabled(true);

    if(resetInput){
        ui->inputLabel->setText("");
    }

    if(rParen){
        ui->inputLabel->setText(ui->inputLabel->text() + " * ");
    }
    ui->inputLabel->setText(ui->inputLabel->text() + "(");

    ui->resultLabel->setText(QString("0"));
    lParenCount++;
    resetInput = false;
    resetResult = false;
    binOp = false;
    lParen = true;
    rParen = false;
    eqPressed = false;
}

void MainWindow::addRparen(){

    QString str = ui->inputLabel->text();

    if(lParen){
        str += " ";
    }
    if(rParen){
        str += ")";
    }
    else{
        str += ui->resultLabel->text() + " )";
    }

    ui->inputLabel->setText(str);
    lParenCount--;
    resetInput = false;
    resetResult = false;
    binOp = false;
    lParen = false;
    rParen = true;

    if(lParenCount == 0){
        ui->bParenR->setEnabled(false);
    }
}

void MainWindow::reciproc(){
    QString str = ui->resultLabel->text();
    ui->resultLabel->setText("1");
    QMetaObject::invokeMethod(ui->bDiv, "clicked");
    ui->resultLabel->setText(str);
}
