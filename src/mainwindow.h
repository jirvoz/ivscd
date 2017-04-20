#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <cdmath.h>
#include <math.h>
#include <QMessageBox>


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

    void openAbout();

    void quitButton();

    void addFunction();

    void inputDelete();

private:
    Ui::MainWindow *ui;
    void clearFlags();
    int lParenCount = 0;


    CDMath math;

    double memory = 0.;

    enum class eventFlag{
        None, Num, binOp, lParen, rParen, eqPressed, clearAll, Mem
    };

    eventFlag event = eventFlag::None;


};

#endif // MAINWINDOW_H
