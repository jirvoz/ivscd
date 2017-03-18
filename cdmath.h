#ifndef CDMATH_H
#define CDMATH_H

#include <QString>
#include <QStack>

class CDMath
{
public:
    CDMath();
    static double power(double a, double b);
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
};

#endif // CDMATH_H
