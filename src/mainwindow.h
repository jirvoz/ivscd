#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cdmath.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_B_0_clicked();
    void on_B_1_clicked();
    void on_B_2_clicked();
    void on_B_3_clicked();
    void on_B_4_clicked();
    void on_B_5_clicked();
    void on_B_6_clicked();
    void on_B_7_clicked();
    void on_B_8_clicked();
    void on_B_9_clicked();
    void on_B_plus_clicked();
    void on_B_minus_clicked();
    void on_B_times_clicked();
    void on_B_div_clicked();
    void on_B_rightBrace_clicked();
    void on_B_leftBrace_clicked();
    void on_B_equals_clicked();

private:
    Ui::MainWindow *ui;
    CDMath cdMath;

};

#endif // MAINWINDOW_H
