#include <iostream>
#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <vector>

#include "sdeviation.h"
#include "cdmath.h"

using namespace std;

double standardDeviation(int paramCount, double *items)
{
    double sum = 0.0;

    for(int i = 0; i < paramCount; i++)
    {
        sum += CDMath::power(items[i], 2.0);
    }

    double mean = CDMath::mean(paramCount, items);

    double subRes = sum - (paramCount * CDMath::power(mean, 2.0));

    double res;
    res = (1.0/(paramCount - 1.0)) * subRes;
    res = CDMath::squareRoot(res, 2.0);

    return res;
}

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		perror("Malo argumentov !\n");
		return 1;
	}
	//vector<double> items;
	double filing[2000];

	int i = 0;

	int max = atoi(argv[1]);

	while((scanf("%lf", &filing[i])))
	{
		//items.push_back(filing[i]);
		i++;

		if(i == max)
		{
			break;
		}
	}		
		

	double vysledok	= standardDeviation(i, filing);
	
	cout.precision(17);
	cout << vysledok << endl;
	cout << max << endl;
	cout << i << endl;
	

	return 0;
}
