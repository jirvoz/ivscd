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

private:
    Ui::MainWindow *ui;
    bool resetInput;
    bool resetResult;
    bool binOp;

    CDMath math;

    double memory;

    int lParenCount;


};

#endif // MAINWINDOW_H
