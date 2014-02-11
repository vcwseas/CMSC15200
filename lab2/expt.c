/* Victor Cheung, vcheung */
/* CS152, Winter 2014 */
/* Lab 1 */
#include <stdio.h>
#include "expt.h"

long int expt(int a, unsigned int n)
{
	if (n == 0)
		return 1;
	else if (n == 1)
		return a;
	else return a * expt(a, n - 1);
}

long int ss(int a, unsigned int n)
{
	if (n == 0)
		return 1;

	else if (n % 2 == 0)
	{
		long int temp = ss(a, n/2);
		return temp * temp;
	}
	else
		return a * ss(a, n - 1);
}


int ssm(int a, unsigned int n, unsigned int m)
{
	if (n == 0)
		return 1;
	else if (n % 2 == 0)
	{
		long int temp = ssm(a, n/2);
		return (temp * temp) % m;
	}
	else
		return a * ssm(a, n - 1) % m;
}
