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
     *
     * Evaluates QString expression written in infix notation
     * using Shunting-yard algorithm and calculates it.
     *
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

    /**
     * @brief Assigns precedence and asociativity to passed operator.
     *
     * Creates (changes) record in opProperties array with
     * structure OpProperties containing operator precedence
     * and asociativity.
     *
     * @param op operator, which are properties assigned to
     * @param prec precedence of the operator
     * @param asoc asociativity of the operator
     */
    void initOperator(Operator op, int prec, CDMath::OpAsociativity asoc);

    /**
     * @brief Pushes operator to operator stack with all necessities
     * around it.
     *
     * Before pushing operator to operatorStack commits all operators
     * with higher or equal precedence and left associativity and
     * with higher precedence and right associativity.
     *
     * @param op operator to push
     */
    void pushOperator(Operator op);

    /**
     * @brief Commits operator on the top of operator stack.
     *
     * Pops operator from the top of operatorStack
     * and executes his action.
     */
    void commitTopOperator();
};

#endif // CDMATH_H
