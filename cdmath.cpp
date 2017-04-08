#include <QStack>

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
    initOperator(Operator::POWER, 4, OpAsociativity::RIGHT);
    initOperator(Operator::ABS, 5, OpAsociativity::RIGHT);

    //initialize functions
    functions.insert("abs", Operator::ABS);
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
    case Operator::ABS:
        a = numberStack.pop();
        numberStack.push(a < 0 ? -a : a);
        break;
    default:
        break;
    }
}

double CDMath::power(double a, double b)
{
    //TODO expand this also for not-natural numbers
    double res = 1;

    for (int i = 0; i < b; i++)
        res *= a;

    return res;
}

double CDMath::evaluate(QString expression)
{
    int digitsRead = 0;	//number of consequent digits read
    int lettersRead = 0;	//number of consequent letters (for functions) read
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
        }

        //reading operators
        switch (expression[i].toLatin1()) {
        case '(':
            pushOperator(Operator::PARENTHESIS);
            break;
        case ')':
            while (operatorStack.top() != Operator::PARENTHESIS)
                commitTopOperator();
            commitTopOperator();	//pop parenthesis
            break;
        case '+':
            pushOperator(Operator::ADD);
            break;
        case '-':
            pushOperator(Operator::SUBTRACT);
            break;
        case '*':
            pushOperator(Operator::MULTIPLY);
            break;
        case '/':
            pushOperator(Operator::DIVIDE);
            break;
        case '^':
            pushOperator(Operator::POWER);
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
