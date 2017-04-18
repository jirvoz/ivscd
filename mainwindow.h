#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <cdmath.h>



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

    void keyPressEvent(QKeyEvent *event );

private:
    Ui::MainWindow *ui;
    bool resetInput;
    bool resetResult;
    bool binOp;

    CDMath math;

    double memory;


};

#endif // MAINWINDOW_H
