#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <cdmath.h>
#include <math.h>
#include <QMessageBox>
#include <QListWidget>

/**
 * @brief Main class of the Application, which holds all widget methods.
 */
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
    /**
     * @brief Adds a number.
     * Adds a decimal (0-9) number to the resultLabel.
     * Sets event to Num.
     * Event handler for buttonpress.
     * Number added is taken from the button text.
     */
    void addNum();

    /**
     * @brief Adds a binary operator.
     * Adds a binary operator along with resultLabel to the inputLabel.
     * Wraps negative numbers in parenthesis.
     * Sets event to binOp.
     * Changes operators, if last event is binOp.
     * Omits resultLabel after )
     * Operators: + - * / %
     * Event handler for buttonpress.
     * Operator added is taken from the button text.
     */
    void addBinOp();

    /**
     * @brief Evaluates expression.
     * Evaluates expression given by inputLabel and resultLabel.
     * Omits result label, after ).
     * Event handler for buttonpress.
     */
    void equalsPressed();

    /**
     * @brief Adds a dot.
     * Adds a dot to resultLabel if there isn't one alredy.
     * If the string is "-" only, adds " 0" string.
     * Disabled after equals.
     * Event handler for buttonpress.
     */
    void addDot();

    /**
     * @brief Toggles the sign.
     * Toggles the sign of the expression on the resultLabel.
     * Disabled after equals.
     * Event handler for buttonpress.
     */
    void toggleSign();

    /**
     * @brief Removes character.
     * Removes a character from resultLabel.
     * Event handler for buttonpress.
     */
    void backSpace();

    /**
     * @brief Clears resultLabel.
     * Event handler for buttonpress.
     */
    void clear();

    /**
     * @brief Clears everything, besides memory.
     * Event handler for buttonpress.
     */
    void clearAll();

    /**
     * @brief Sets Pi constant to resultLabel.
     * Event handler for buttonpress.
     */
    void setPi();

    /**
     * @brief Sets Pi constant to resultLabel.
     * Event handler for buttonpress.
     */
    void setEuler();

    /**
     * @brief Handles keyboard input.
     * @param event QKeyEvent object with event information.
     * Calls animation of buttons.
     */
    void keyPressEvent(QKeyEvent *event );

    /**
     * @brief Sets memory from resultLabel.
     * Event handler for buttonpress.
     */
    void memorySet();

    /**
     * @brief Sets memory to zero.
     * Event handler for buttonpress.
     */
    void memoryClear();

    /**
     * @brief Sets resultLabel to memory.
     * Event handler for buttonpress.
     */
    void memoryRead();

    /**
     * @brief Adds resultLabel to memory.
     * Event handler for buttonpress.
     */
    void memoryAdd();

    /**
     * @brief Subtracts resultLabel from memory.
     * Event handler for buttonpress.
     */
    void memorySub();

    /**
     * @brief Adds ) to inputLabel.
     * Event handler for buttonpress.
     */
    void addLparen();

    /**
     * @brief Adds ) to inputLabel.
     * Event handler for buttonpress.
     */
    void addRparen();

    /**
     * @brief Adds 1 / ( to inputLabel.
     * Event handler for buttonpress.
     */
    void reciproc();

    /**
     * @brief Opens About window.
     * Event handler for buttonpress.
     */
    void openAbout();

    /**
     * @brief Quits the application.
     * Event handler for buttonpress.
     */
    void quitButton();

    /**
     * @brief Adds function to inputLabel.
     * Event handler for buttonpress.
     */
    void addFunction();

    /**
     * @brief Switches to text input.
     * Event handler for buttonpress.
     */
    void textInput();

    /**
     * @brief Switches to basic input.
     * Event handler for buttonpress.
     */
    void basicInput();

    /**
     * @brief Calculates expression at lineEdit.
     * Event handler for buttonpress.
     */
    void calcInput();

    /**
     * @brief Editor generated function.
     * @param arg1 Reference to string in line edit.
     * Event handler for lineEdit.
     */
    void on_lineEdit_textEdited(const QString &arg1);

    /**
     * @brief Switches to sDev input.
     * Event handler for buttonpress.
     */
    void sDev();

    /**
     * @brief Clears history.
     * Event handler for buttonpress.
     */
    void clearList();

    /**
     * @brief Adds selected text to input.
     * Event handler for buttonpress.
     */
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:

    /**
     * @brief Editor generated code.
     */
    Ui::MainWindow *ui;

    /**
     * @brief Clears neccesary things after events.
     */
    void clearFlags();

    /**
     * @brief Counter for parenthesis.
     */
    int lParenCount = 0;

    /**
     * @brief Instance of math library.
     */
    CDMath math;

    /**
     * @brief Variable for memory.
     */
    double memory = 0.;

    /**
     * @brief Type of last event.
     */
    enum class eventFlag{
        None, Num, binOp, lParen, rParen, eqPressed, clearAll, Mem, setMem
    };

    /**
     * @brief Event flag variable for the application.
     */
    eventFlag event = eventFlag::None;

    /**
     * @brief Helper flag for sDeviation.
     */
    bool sDevChecked = false;


};

#endif // MAINWINDOW_H
