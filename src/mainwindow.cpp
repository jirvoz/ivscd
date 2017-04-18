#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cdMath = CDMath();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText(QString::number(cdMath.evaluate(ui->lineEdit->text())));
}
*/

void MainWindow::on_B_0_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "0");
}

void MainWindow::on_B_1_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "1");
}

void MainWindow::on_B_2_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "2");
}

void MainWindow::on_B_3_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "3");
}

void MainWindow::on_B_4_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "4");
}

void MainWindow::on_B_5_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "5");
}

void MainWindow::on_B_6_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "6");
}

void MainWindow::on_B_7_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "7");
}

void MainWindow::on_B_8_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "8");
}

void MainWindow::on_B_9_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "9");
}

void MainWindow::on_B_plus_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "+");
}

void MainWindow::on_B_minus_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "-");
}

void MainWindow::on_B_times_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "*");
}

void MainWindow::on_B_div_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "/");
}

void MainWindow::on_B_leftBrace_clicked()
{
    ui->inputField->setText(ui->inputField->text() + "(");
}

void MainWindow::on_B_rightBrace_clicked()
{
    ui->inputField->setText(ui->inputField->text() + ")");
}

void MainWindow::on_B_equals_clicked()
{

    ui->resultLabel->setText(QString::number(cdMath.evaluate(ui->inputField->text())));
    ui->inputField->setText(QString(""));
}










