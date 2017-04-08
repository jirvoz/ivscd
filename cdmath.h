#ifndef CDMATH_H
#define CDMATH_H

#include <QString>
#include <QMap>
#include <QStack>

class CDMath
{
public:
    CDMath();

    /**
     * @brief Exponentiates base to exponent
     * @param a base
     * @param b exponent
     * @return a^b
     */
    static double power(double a, double b);

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
                          ABS,
                          OPERATORS_COUNT
                        };

    enum class OpAsociativity { NONE, LEFT, RIGHT };

    struct OpProperties {
        int precedence;
        OpAsociativity asociativity;
    };

    OpProperties opProperties[(int)Operator::OPERATORS_COUNT];
    QMap<QString, Operator> functions;
    QStack<double> numberStack;
    QStack<Operator> operatorStack;

    int getOpPrecedence(Operator op);
    OpAsociativity getOpAsociativity(Operator op);

    void initOperator(Operator op, int prec, CDMath::OpAsociativity asoc);
    void pushOperator(Operator op);
    void commitTopOperator();
};

#endif // CDMATH_H
