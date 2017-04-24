#include <iostream>

#include "cdmath.h"

CDMath::CDMath()
{


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

double CDMath::mean(int paramCount, double *items)
{

    double mean = 0;

    for(int i = 0; i < paramCount; i++)
    {
        mean += items[i];
    }

    return mean/paramCount;
}


double CDMath::standardDeviation(int paramCount, double *items)
{
    double sum = 0;

    for(int i = 0; i < paramCount; i++)
    {
        sum += CDMath::power(items[i], 2);
    }

    double mean = CDMath::mean(paramCount, items);

    double subRes = sum - (paramCount * CDMath::power(mean, 2));

    double res;
    res = (1.0/(paramCount - 1)) * subRes;
    res = CDMath::squareRoot(res, 2);

    return res;
}
