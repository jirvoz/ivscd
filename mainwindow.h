#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <cdmath.h>
#include <math.h>



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
    void addNum();
    void addBinOp();
    void equalsPressed();
    void addDot();
    void toggleSign();

    void backSpace();
    void clear();
    void clearAll();

    void setPi();
    void setEuler();

    void keyPressEvent(QKeyEvent *event );

    void memorySet();
    void memoryClear();
    void memoryRead();
    void memoryAdd();
    void memorySub();

    void addLparen();
    void addRparen();

    void reciproc();

private:
    Ui::MainWindow *ui;
    bool resetInput = false;
    bool resetResult = false;
    bool binOp = false;
    int lParenCount = 0;
    bool lParen = false;
    bool rParen = false;
    bool eqPressed = false;

    CDMath math;

    double memory = 0.;



};

#endif // MAINWINDOW_H
