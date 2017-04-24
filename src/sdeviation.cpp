#include <QString>

#include "sdeviation.h"
#include "cdmath.h"



double standardDeviation(int paramCount, double *items)
{
    double sum = 0;
    for(int i = 0; i < paramCount; i++)
    {
        sum += CDMath::power(items[i], 2);
    }

    double mean = 0;

    for(int i = 0; i < paramCount; i++)
    {
        mean += items[i];
    }

    mean = mean/paramCount;

    double subRes = sum - (paramCount * CDMath::power(mean, 2));

    double res;
    res = (1.0/(paramCount - 1)) * subRes;
    res = CDMath::squareRoot(res, 2);

    return res;
}


void sdGetItems(QString input)
{
    int paramCount = 0;
//    bool ok;
    double *items;

    QStringList itemsList = input.split(' ');

    items = new double (sizeof(double) * itemsList.size());

    foreach(QString str, itemsList)
    {
        for(int i = 0; i < itemsList.size(); i++)
        {
            items[i] = str.toDouble();
        }
    }


    while(items[paramCount])
    {
        paramCount++;
    }

    standardDeviation(paramCount + 1, items);

}
