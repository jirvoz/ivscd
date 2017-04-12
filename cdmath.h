#ifndef CDMATH_H
#define CDMATH_H

#include <QString>
#include <QStack>

class CDMath
{
public:
    CDMath();

    /**
     * @brief Exponentiates base to exponent
     * @param x base
     * @param y exponent
     * @return x^y
     */
    static double power(double x, double y);

    /**
     * @brief Evaluates and calculates expression passed in QString
     * Evaluates QString expression written in infix notation
     * using Shunting-yard algorithm and calculates it.
     * @param expression expression in QString to evaluate
     * @return numeric result of expression
     */
    double evaluate(QString expression);

private:
    enum class Operator { PARENTHESIS,
                          ADD,
                          SUBTRACT,
                          MULTIPLY,
                          DIVIDE,
                          POWER,
                          OPERATORS_COUNT
                        };

    enum class OpAsociativity { NONE, LEFT, RIGHT };

    struct OpProperties {
        int precedence;
        OpAsociativity asociativity;
    };

    OpProperties opProperties[(int)Operator::OPERATORS_COUNT];
    QStack<double> numberStack;
    QStack<Operator> operatorStack;

    int getOpPrecedence(Operator op);
    OpAsociativity getOpAsociativity(Operator op);

    void initOperator(Operator op, int prec, CDMath::OpAsociativity asoc);
    void pushOperator(Operator op);
    void commitTopOperator();

    /**
     * @brief Calculates natural logarithm of a number
     * @param x number
     * @return ln(x)
     */
    static double ln(double x);

    /**
     * @brief cfrac formula to help calculate ln(x)
     * @param a an auxiliary number for Taylor series
     * @param num number in numerator
     * @param n number of iterations
     * @param powz z*z; z is a formula z = (x - 1) / (x + 1)
     * @return
     */
    static double cfrac(double a, double number, unsigned int n, double powz);

    /**
     * @brief If necessary, transforms signed integer to its' unsigned value
     * @param n number
     * @return absolute value of a number
     */
    static double fabs(double n);
};

#endif // CDMATH_H
