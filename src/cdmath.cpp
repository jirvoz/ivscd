#include <QStack>
#include <cmath>

#include "cdmath.h"

CDMath::CDMath()
{
    //initialize operators
    //higher is better
    initOperator(Operator::PARENTHESIS, 1, OpAsociativity::NONE);
    initOperator(Operator::ADD, 2, OpAsociativity::LEFT);
    initOperator(Operator::SUBTRACT, 2, OpAsociativity::LEFT);
    initOperator(Operator::MULTIPLY, 3, OpAsociativity::LEFT);
    initOperator(Operator::DIVIDE, 3, OpAsociativity::LEFT);
    initOperator(Operator::MOD, 3, OpAsociativity::LEFT);
    initOperator(Operator::POWER, 4, OpAsociativity::RIGHT);
    initOperator(Operator::SQRT, 5, OpAsociativity::RIGHT);
    initOperator(Operator::ABS, 5, OpAsociativity::RIGHT);
    initOperator(Operator::SIN, 5, OpAsociativity::RIGHT);
    initOperator(Operator::COS, 5, OpAsociativity::RIGHT);
    initOperator(Operator::TAN, 5, OpAsociativity::RIGHT);
    initOperator(Operator::LN, 5, OpAsociativity::RIGHT);
    initOperator(Operator::LOG, 5, OpAsociativity::RIGHT);

    //initialize functions
    functions.insert("sqrt", Operator::SQRT);
    functions.insert("abs", Operator::ABS);
    functions.insert("sin", Operator::SIN);
    functions.insert("cos", Operator::COS);
    functions.insert("tan", Operator::TAN);
    functions.insert("tg", Operator::TAN); //alias for tan
    functions.insert("ln", Operator::LN);
    functions.insert("log", Operator::LOG);
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
    case Operator::MOD:
        b = numberStack.pop();
        a = numberStack.pop();
        //because of doubles
        numberStack.push(a - b * floor(a / b));
        break;
    case Operator::POWER:
        b = numberStack.pop();
        a = numberStack.pop();
        numberStack.push(power(a, b));
        break;
    case Operator::SQRT:
        a = numberStack.pop();
        numberStack.push(power(a, 0.5));
        break;
    case Operator::ABS:
        a = numberStack.pop();
        numberStack.push(a < 0 ? -a : a);
        break;
    case Operator::SIN:
        a = numberStack.pop();
        numberStack.push(sin(a));
        break;
    case Operator::COS:
        a = numberStack.pop();
        numberStack.push(cos(a));
        break;
    case Operator::TAN:
        a = numberStack.pop();
        numberStack.push(tan(a));
        break;
    case Operator::LN:
        a = numberStack.pop();
        numberStack.push(log(a));
        break;
    case Operator::LOG:
        a = numberStack.pop();
        numberStack.push(log10(a));
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

double CDMath::squareRoot(double a, double b)
{
   double y = 1/b;
   return power(a, y);
}

double CDMath::evaluate(QString expression)
{
    bool lastWasNumber = false;
    int digitsRead = 0;	//number of consequent digits read
    int lettersRead = 0; //number of consequent letters (for functions) read
    int expLength = expression.length();

    numberStack.clear();
    operatorStack.clear();

    for (int i = 0; i < expLength; i++)
    {
        //reading number
        if (expression[i].isDigit() || expression[i] == '.'
            //check for unary minus
            || (expression[i] == '-' && digitsRead == 0
                && (!lastWasNumber || (!lastWasNumber && !operatorStack.isEmpty()
                    && operatorStack.top() == Operator::PARENTHESIS))))
        {
            digitsRead++;
            continue;
        }
        else if (digitsRead)
        {
            numberStack.push(expression.midRef(i - digitsRead, digitsRead).toDouble());
            digitsRead = 0;
            lastWasNumber = true;
        }

        //reading letters (for functions)
        if (expression[i].isLower())
        {
            lettersRead++;
            continue;
        }
        else if (lettersRead)
        {
            pushOperator(functions.value(expression.mid(i - lettersRead, lettersRead)));
            lettersRead = 0;
            lastWasNumber = false;
        }

        //reading operators
        switch (expression[i].toLatin1()) {
        case '(':
            pushOperator(Operator::PARENTHESIS);
            lastWasNumber = false;
            break;
        case ')':
            while (operatorStack.top() != Operator::PARENTHESIS)
                commitTopOperator();
            commitTopOperator();    //pop parenthesis
            //no lastWasNumber=false, parenthesis is number after evaluation
            break;
        case '+':
            pushOperator(Operator::ADD);
            lastWasNumber = false;
            break;
        case '-':
            pushOperator(Operator::SUBTRACT);
            lastWasNumber = false;
            break;
        case '*':
            pushOperator(Operator::MULTIPLY);
            lastWasNumber = false;
            break;
        case '/':
            pushOperator(Operator::DIVIDE);
            lastWasNumber = false;
            break;
        case '%':
            pushOperator(Operator::MOD);
            lastWasNumber = false;
            break;
        case '^':
            pushOperator(Operator::POWER);
            lastWasNumber = false;
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
