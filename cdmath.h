#ifndef CDMATH_H
#define CDMATH_H

#include <QString>
#include <QStack>

class CDMath
{
public:
    CDMath();
    static double Add(double a, double b);
    static double Power(double a, double b);
    double Evaluate(QString expression);

private:
    enum class Operator : int { ADD, SUBTRACT, MULTIPLY, DIVIDE, POWER, OPERATORS_COUNT };
    enum class OpAsociativity { NONE, LEFT, RIGHT };

    struct OpProperties {
        int precedence;
        OpAsociativity asociativity;
    };

    OpProperties opProperties[(int)Operator::OPERATORS_COUNT];
    QStack<double> numberStack;
    QStack<Operator> operatorStack;

    void InitOperator(Operator op, int prec, CDMath::OpAsociativity asoc);
    void PushOperator(Operator op);
    void CommitOperator();
};

#endif // CDMATH_H
