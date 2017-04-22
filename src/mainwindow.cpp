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


    // helper lists for initializations
    // numbers
    QPushButton* numLst[] = {ui->b0, ui->b1, ui->b2, ui->b3, ui->b4, ui->b5, ui->b6, ui->b7, ui->b8, ui->b9 };

    for(auto i:numLst){

        connect(i, SIGNAL(clicked()), this, SLOT(addNum()));

    }
    // binary operators
    QPushButton* binOpLst[] = {ui->bAdd, ui->bDiv, ui->bPower, ui->bSub, ui->bTimes, ui->bMod };

    for(auto i:binOpLst){

        connect(i, SIGNAL(clicked()), this, SLOT(addBinOp()));

    }
    // functions
    QPushButton* funcList[] = {ui->bLog, ui->bLn, ui->bSin, ui->bCos, ui->bTan, ui->bSqrt, ui->bAbs };

    for(auto i:funcList){

        connect(i, SIGNAL(clicked()), this, SLOT(addFunction()));

    }
    // manual event handler initializations

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

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addNum(){

    clearFlags();

    // get the caller's number
    QString num = qobject_cast<QPushButton*>(sender())->text();
    QString str = ui->resultLabel->text();

    // replace 0 with number
    if(str == QString("0")){
        str = num;
    }
    else{
        // add a space to the number if, it is negative and there is no other number
        if(str == "-"){
            str += " ";
        }
        // append the caller's number
        str += num;
    }

    ui->resultLabel->setText(str);

    event = eventFlag::Num;

}

void MainWindow::addBinOp(){

    // clear stuff only once
    if(event != eventFlag::binOp){
        clearFlags();
    }
    QString str = ui->inputLabel->text();

    // change operator, if the last event was binary operator
    if(event == eventFlag::binOp){
        str = str.left(str.length() - 2) + qobject_cast<QPushButton*>(sender())->text() + " ";
    }
    // only add the operator if the last action was )
    else if(str.right(1) == ")"){
        str += " " + qobject_cast<QPushButton*>(sender())->text() + " ";
    }
    else{
        // add parenthesis to negative numbers if neccessary
        if(ui->resultLabel->text().left(1) == QString("-") && ui->inputLabel->text().length() > 0 && str.right(1) != "("){
            str += "( " + ui->resultLabel->text() + " ) " + qobject_cast<QPushButton*>(sender())->text() + " ";
        }
        else{
            // add space if neccessary
            if(str.right(1) == "("){
                str += QString(" ");
            }
            // add operator
            str += ui->resultLabel->text() + " " + qobject_cast<QPushButton*>(sender())->text() + " ";
        }
    }

    ui->inputLabel->setText(str);

    event = eventFlag::binOp;

}

void MainWindow::equalsPressed(){
    if(event != eventFlag::eqPressed && ui->inputLabel->text().length() > 0){

        QString str;
        // omit result label
        if(event == eventFlag::rParen){
             str = ui->inputLabel->text();
        }
        else{
             str = ui->inputLabel->text();
             if(str.right(1) == "("){
                 str += QString(" ");
             }
             QString tmp = ui->resultLabel->text();
             if(tmp.left(1) == "-" && str.right(1) != "("){
                 tmp = "( " + tmp + " )";
             }
             str += tmp;
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
        try{
            ui->resultLabel->setText(QString::number(math.evaluate(str)));
        }
        catch(CDMathException e){
            ui->infoLabel->setText(e.what());
        }

        event = eventFlag::eqPressed;
    }
}

void MainWindow::addDot(){
    // disable dot adding after calculation
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

    if(event != eventFlag::eqPressed){
        QString str = ui->resultLabel->text();
        // zero can't be negative
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
}

void MainWindow::backSpace(){

    if(event != eventFlag::eqPressed){

        clearFlags();

        QString str = ui->resultLabel->text();
        do{
            str.chop(1);
            }
        while(str.right(1) == " ");

        event = eventFlag::Num;

        if(str.length() == 0){
            str = "0";
        }
        ui->resultLabel->setText(str);
    }
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

    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
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
        ui->bAbs->animateClick();
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
    if(event != eventFlag::setMem){
        clearFlags();
    }
    memory = ui->resultLabel->text().toDouble();
    event = eventFlag::setMem;
    ui->memLabel->setText(QString::number(memory, 'f', 1));
}

void MainWindow::memoryClear(){

    memory = 0;
    ui->memLabel->setText("0");
}

void MainWindow::memoryRead(){

    clearFlags();
    ui->resultLabel->setText(QString::number(memory));
    event = eventFlag::Mem;
}

void MainWindow::memoryAdd(){

    clearFlags();
    memory += ui->resultLabel->text().toDouble();
    ui->memLabel->setText(QString::number(memory, 'f', 1));
}

void MainWindow::memorySub(){

    clearFlags();
    memory -= ui->resultLabel->text().toDouble();
    ui->memLabel->setText(QString::number(memory, 'f', 1));

}

void MainWindow::addLparen(){

    clearFlags();

    ui->bParenR->setEnabled(true);

    if(event == eventFlag::rParen){
        ui->inputLabel->setText(ui->inputLabel->text() + " * ");
    }
    ui->inputLabel->setText(ui->inputLabel->text() + "(");

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

    if(event == eventFlag::rParen){
        ui->inputLabel->setText(ui->inputLabel->text() + " * ");
    }

    QString str = ui->resultLabel->text();
    if(str.right(1) == "("){
        str += QString(" ");
    }
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

    if(event == eventFlag::clearAll || event == eventFlag::binOp || event == eventFlag::Mem || event == eventFlag::eqPressed
                                    || event == eventFlag::rParen || event == eventFlag::setMem){

        ui->resultLabel->setText("0");
    }

    if(event == eventFlag::clearAll || event == eventFlag::eqPressed){
        ui->infoLabel->setText("");
    }

    if(event == eventFlag::clearAll){
        lParenCount = 0;
        ui->bParenR->setEnabled(false);
    }
}

void MainWindow::quitButton(){
    QApplication::quit();
}

void MainWindow::addFunction(){

    clearFlags();

    if(event == eventFlag::rParen){
        ui->inputLabel->setText(ui->inputLabel->text() + " * ");
    }

    QString str = ui->inputLabel->text();

    if(str.right(1) == "("){
        str += QString(" ");
    }
    QString tmp;

    if(sender() == ui->bSqrt){
        tmp = "sqrt";
    }
    else{
        tmp = qobject_cast<QPushButton*>(sender())->text();
    }
    str += tmp;

    ui->inputLabel->setText(str);
    event = eventFlag::None;
    QMetaObject::invokeMethod(ui->bParenL, "clicked");

}
