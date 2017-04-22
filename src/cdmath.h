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
     * @param x base
     * @param y exponent
     * @return x^y
     */
    static double power(double x, double y);

    /**
     * @brief computes the square root of number
     * @param a base
     * @param b square root
     * @return a^(1/b)
     */
    static double squareRoot(double a, double b);


    /**
     * @brief computes mean of the items file
     * @param paramCount the number of items in file
     * @param items file of the values to compute with
     * @return mean
     */
    static double mean(int paramCount, double *items);

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

    /**
     * @brief Returns the standard deviation of double values passed as sec. arg.
     * @param paramCount number of double values entered
     * @param items array of double values to compute with
     * @return standard deviation of items
     */
    double standardDeviation(int paramCount, double *items);

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
