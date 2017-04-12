#include <QStack>

#include "cdmath.h"

CDMath::CDMath()
{
    //initialize operators
    initOperator(Operator::PARENTHESIS, 5, OpAsociativity::NONE);
    initOperator(Operator::ADD, 4, OpAsociativity::LEFT);
    initOperator(Operator::SUBTRACT, 4, OpAsociativity::LEFT);
    initOperator(Operator::MULTIPLY, 3, OpAsociativity::LEFT);
    initOperator(Operator::DIVIDE, 3, OpAsociativity::LEFT);
    initOperator(Operator::POWER, 2, OpAsociativity::RIGHT);
}

int CDMath::getOpPrecedence(Operator op)
{
    return opProperties[(int)op].precedence;
}

CDMath::OpAsociativity CDMath::getOpAsociativity(Operator op)
{
    return opProperties[(int)op].asociativity;
}

void CDMath::initOperator(Operator op, int prec, OpAsociativity asoc)
{
    OpProperties props = { prec, asoc };
    opProperties[(int)op] = props;
}

void CDMath::pushOperator(Operator op)
{
    //while previous operators have better precedence
    while (!operatorStack.isEmpty() &&
        ((getOpAsociativity(op) == OpAsociativity::LEFT
          && getOpPrecedence(op) <= getOpPrecedence(operatorStack.top()))
        || (getOpAsociativity(op) == OpAsociativity::RIGHT
            && getOpPrecedence(op) < getOpPrecedence(operatorStack.top()))))
    {
        //commit top operator
        commitTopOperator();
    }

    operatorStack.push(op);
}

void CDMath::commitTopOperator()
{
    Operator op = operatorStack.pop();
    double a, b;

    switch (op) {
    case Operator::ADD:
        b = numberStack.pop();
        a = numberStack.pop();
        numberStack.push(a + b);
        break;
    case Operator::SUBTRACT:
        b = numberStack.pop();
        a = numberStack.pop();
        numberStack.push(a - b);
        break;
    case Operator::MULTIPLY:
        b = numberStack.pop();
        a = numberStack.pop();
        numberStack.push(a * b);
        break;
    case Operator::DIVIDE:
        b = numberStack.pop();
        a = numberStack.pop();
        numberStack.push(a / b);
        break;
    case Operator::POWER:
        b = numberStack.pop();
        a = numberStack.pop();
        numberStack.push(power(a, b));
        break;
    default:
        break;
    }
}


double CDMath::power(double x, double y)
{
    double num = 1.0; //numerator
    double denum = 1.0; //denumerator
    double fact = 1.0; //factorial
    double res = 1; //result
    double frac = 0; //fraction
    double pfrac = 0; //previous fraction

    if (x > 0)
    {
        do
        {
            pfrac = frac; //store previous fraction for checking condition
            num *= y * ln(x);
            denum *= fact;
            fact++;
            frac = num / denum; //new fraction
            res += frac;

        } while (!(fabs(frac - pfrac) <= 1e-12));

        return res;
    }
    else // if base is negative, exponent must be integer
    {
        if (y < 0)
        {
            for (int i = 0; i < -(y); i++)
                res /= x;

            return res;
        }
        else
        {
            for (int i = 0; i < y; i++)
                res *= x;

            return res;
        }
    }
}

double CDMath::ln(double x)
{
    double	z = (x - 1) / (x + 1);

    return 2 * z / cfrac(-1, 0, 500, z*z);
}

double CDMath::cfrac(double a, double num, unsigned int n, double powz)
{
    a += 2;
    num += a;

    if (n == 0)
        return 1;
    else
        return a - ((num*powz)/ cfrac(a,num,(n - 1),powz));

}

double CDMath::fabs(double n)
{
    return (n >= 0) ? n : -(n);
}

double CDMath::evaluate(QString expression)
{
    int digitsRead = 0;	//number of consequent digits read
    int expLength = expression.length();

    numberStack.clear();
    operatorStack.clear();

    for (int i = 0; i < expLength; i++)
    {
        //reading number
        if (expression[i].isDigit() || expression[i] == '.')
        {
            digitsRead++;
            continue;
        }
        else if (digitsRead)
        {
            numberStack.push(expression.midRef(i - digitsRead, digitsRead).toDouble());
            digitsRead = 0;
        }

        //reading operators
        switch (expression[i].toLatin1()) {
        case '(':
            operatorStack.push(Operator::PARENTHESIS);
            break;
        case ')':
            while (operatorStack.top() != Operator::PARENTHESIS)
                commitTopOperator();
            commitTopOperator();	//pop parenthesis
            break;
        case '+':
            operatorStack.push(Operator::ADD);
            break;
        case '-':
            operatorStack.push(Operator::SUBTRACT);
            break;
        case '*':
            operatorStack.push(Operator::MULTIPLY);
            break;
        case '/':
            operatorStack.push(Operator::DIVIDE);
            break;
        case '^':
            operatorStack.push(Operator::POWER);
            break;
        default:
            break;
        }
    }

    if (digitsRead)
        numberStack.push(expression.midRef(expLength - digitsRead, digitsRead).toDouble());

    while (!operatorStack.isEmpty())
    {
        commitTopOperator();
    }

    return numberStack.pop();
}
