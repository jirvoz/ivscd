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

    connect(ui->bAbout, SIGNAL(clicked()), this, SLOT(openAbout()));

    connect(ui->bExit, SIGNAL(clicked()), this, SLOT(quitButton()));

    ui->longinputLabel->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addNum(){

    clearFlags();

    QString num = qobject_cast<QPushButton*>(sender())->text();
    QString str = ui->resultLabel->text();

    if(str == QString("0")){
        str = num;
    }
    else{
        if(str == "-"){
            str += " ";
        }
        str += num;
    }

    ui->resultLabel->setText(str);

    event = eventFlag::Num;

}

void MainWindow::addBinOp(){

    clearFlags();

    QString str = ui->inputLabel->text();

    if(event == eventFlag::binOp){
        str = str.left(str.length() - 2) + qobject_cast<QPushButton*>(sender())->text() + " ";
    }
    else if(event == eventFlag::rParen){
        str += " " + qobject_cast<QPushButton*>(sender())->text() + " ";
    }
    else{
        if(ui->resultLabel->text().left(1) == QString("-") && ui->inputLabel->text().length() > 0 && event != eventFlag::lParen ){
            str += "( " + ui->resultLabel->text() + " ) " + qobject_cast<QPushButton*>(sender())->text() + " ";
        }
        else{
            if(event == eventFlag::lParen){
                str += QString(" ");
            }

            str += ui->resultLabel->text() + " " + qobject_cast<QPushButton*>(sender())->text() + " ";
        }
    }

    ui->inputLabel->setText(str);

    event = eventFlag::binOp;

}

void MainWindow::equalsPressed(){
    if(event != eventFlag::eqPressed){

        clearFlags();

        QString str;
        if(event == eventFlag::rParen){
             str = ui->inputLabel->text();
        }
        else{
             str = ui->inputLabel->text() + ui->resultLabel->text();
        }
        if(lParenCount > 0){
            if(event != eventFlag::rParen){
                str += " ";
            }
            for(int i = 0; i < lParenCount; i++){
                str += ")";
            }
        }

        ui->inputLabel->setText(str);

        ui->resultLabel->setText(QString::number(math.evaluate(str)));
    }

    event = eventFlag::eqPressed;
}

void MainWindow::addDot(){
    if(event != eventFlag::eqPressed){

        clearFlags();
        QString str = ui->resultLabel->text();

        if(str.count('.') == 0){
            if(str == "-"){
                str += " 0";
            }

            ui->resultLabel->setText(str + ".");
            event = eventFlag::Num;
        }

    }
}

void MainWindow::toggleSign(){


    QString str = ui->resultLabel->text();
    if(str != "0" && str != "0."){

        clearFlags();

        if(str.left(1) == QString("-")){
            str = str.right(str.length() - 2);

        }
        else{
            str = "- " + str;
        }

        ui->resultLabel->setText(str);
        event = eventFlag::Num;

    }
}

void MainWindow::backSpace(){

    clearFlags();

    QString str = ui->resultLabel->text();
    do{
        str.chop(1);
        }
    while(str.right(1) == " ");

    if(str.length() == 0){
        str = "0";
    }
    ui->resultLabel->setText(str);

    event = eventFlag::Num;
}

void MainWindow::clear(){

   clearFlags();
   ui->resultLabel->setText(QString("0"));
   event = eventFlag::Num;
}

void MainWindow::clearAll(){

   event = eventFlag::clearAll;
   clearFlags();

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
    if(event->key() == Qt::Key_F1){
        openAbout();
    }
}

void MainWindow::setPi(){
    clearFlags();
    ui->resultLabel->setText(QString::number(M_PI, 'g', 15));
    event = eventFlag::Num;
}

void MainWindow::setEuler(){
    clearFlags();
    ui->resultLabel->setText(QString::number(M_E, 'g', 15));
    event = eventFlag::Num;
}

void MainWindow::memorySet(){
    clearFlags();
    memory = ui->resultLabel->text().toDouble();
    event = eventFlag::Mem;
}

void MainWindow::memoryClear(){

    memory = 0;

}

void MainWindow::memoryRead(){

    clearFlags();
    ui->resultLabel->setText(QString::number(memory));
    event = eventFlag::Mem;
}

void MainWindow::memoryAdd(){

    clearFlags();
    memory += ui->resultLabel->text().toDouble();
    event = eventFlag::Mem;
}

void MainWindow::memorySub(){

    clearFlags();
    memory -= ui->resultLabel->text().toDouble();
    event = eventFlag::Mem;
}

void MainWindow::addLparen(){

    ui->bParenR->setEnabled(true);

    clearFlags();

    if(event == eventFlag::rParen){
        ui->inputLabel->setText(ui->inputLabel->text() + " * ");
    }
    ui->inputLabel->setText(ui->inputLabel->text() + "(");

    ui->resultLabel->setText(QString("0"));
    lParenCount++;
    event = eventFlag::lParen;
}

void MainWindow::addRparen(){

    clearFlags();

    QString str = ui->inputLabel->text();

    if(event == eventFlag::lParen){
        str += " ";
    }
    if(event == eventFlag::rParen){
        str += ")";
    }
    else{
        str += ui->resultLabel->text() + " )";
    }

    ui->inputLabel->setText(str);
    lParenCount--;
    event = eventFlag::rParen;

    if(lParenCount == 0){
        ui->bParenR->setEnabled(false);
    }
}

void MainWindow::reciproc(){

    clearFlags();

    QString str = ui->resultLabel->text();
    ui->resultLabel->setText("1");
    QMetaObject::invokeMethod(ui->bDiv, "clicked");
    QMetaObject::invokeMethod(ui->bParenL, "clicked");
    ui->resultLabel->setText(str);

}

void MainWindow::openAbout(){

    QMessageBox msgBox;
    msgBox.setText("Simple Calculator app created for IVS 2017.\nCreated by team Core Dumped:\n\n       Dominika Labudová\n       Jozef Méry\n       Vlastimil Rádsetoulal\n       Jiří Vozár");
    msgBox.setWindowTitle("About");
    msgBox.exec();

}

void MainWindow::clearFlags(){

    if(event == eventFlag::clearAll || event == eventFlag::eqPressed){
        ui->inputLabel->setText("");
    }

    if(event == eventFlag::clearAll || event == eventFlag::binOp || event == eventFlag::eqPressed || event == eventFlag::Mem
                                    || event == eventFlag::rParen){

        ui->resultLabel->setText("0");
    }

    if(event == eventFlag::clearAll){
        memory = 0;
        lParenCount = 0;
        ui->bParenR->setEnabled(false);
    }
}

void MainWindow::quitButton(){
    QApplication::quit();
}
