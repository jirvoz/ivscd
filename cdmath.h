#ifndef CDMATH_H
#define CDMATH_H

#include <QString>
#include <QMap>
#include <QStack>

/**
 * @brief Pack of methods for evaluating mathematical expressions.
 */
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
    /**
     * @brief Operator enum for operator stack and properties.
     */
    enum class Operator { PARENTHESIS, ///< opening parenthesis
                          ADD, ///< plus
                          SUBTRACT, ///< minus
                          MULTIPLY, ///< times
                          DIVIDE, ///< division
                          POWER, ///< exponentiation
                          ABS, ///< absolute value
                          OPERATORS_COUNT /**<
                                * last value for OpProperties array
                                *  allocation */
                        };

    /**
     * @brief Asociativity of operators.
     */
    enum class OpAsociativity { NONE, ///< not specified for parenthesis
                                LEFT, ///< left asociativity
                                RIGHT ///< right asociativity
                              };

    /**
     * @brief Struct for storing operator properties.
     */
    struct OpProperties {
        int precedence; ///< precedence of operator
        OpAsociativity asociativity; ///< asociativity of operator
    };

    OpProperties opProperties[(int)Operator::OPERATORS_COUNT]; /**<
        * Table (array) with operator properties
        * like precedence and asociativity. */

    QMap<QString, Operator> functions; /**<
        * List of functions' strings
        * assigned to their operators. */

    QStack<double> numberStack; /**<
        * Stack for numbers waiting for
        * operations to be executed on them. */

    QStack<Operator> operatorStack; /**<
        * Stack for operators waiting for
        * their right time. */

    /**
     * @brief Gets operator precedence.
     * @param op operator
     * @return precedence of operator
     */
    inline int getOpPrecedence(Operator op)
    { return opProperties[(int)op].precedence; }

    /**
     * @brief Gets operator asociativity.
     * @param op operator
     * @return asociatvity of operator
     */
    inline OpAsociativity getOpAsociativity(Operator op)
    { return opProperties[(int)op].asociativity; }

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
