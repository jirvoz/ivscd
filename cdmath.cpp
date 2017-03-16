#include <QStack>

#include "cdmath.h"

double CDMath::Add(double a, double b)
{
    return a + b;
}

double CDMath::Evaluate(QString expression)
{
    int digitsRead = 0;	//number of consequent digits read
    int expLength = expression.length();

    QStack<double> numberStack;

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
    }

    return numberStack.pop();
}
