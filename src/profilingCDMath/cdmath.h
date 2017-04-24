#ifndef CDMATH_H
#define CDMATH_H

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

    /**
     * @brief Asociativity of operators.
     */


    /**
     * @brief Struct for storing operator properties.
     */




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
