/* Victor Cheung, vcheung */
/* CS152, Winter 2014 */
/* Lab 1 */
#include <stdio.h>

long int expt(int a, unsigned int n);
long int ss(int a, unsigned int n);
int ssm(int a, unsigned int n, unsigned int m);

int main()
{
	/* tests for expt */
	printf("Tests for expt\n");
	printf("%ld\n", expt(2,10));	/* 1024 */
	printf("%ld\n", expt(8,9));		/* 134217728 */
	printf("%ld\n", expt(99,4));	/* 96059601 */
	printf("%ld\n", expt(45,5));	/* 184528125 */
	printf("Tests for ss\n");
	printf("%ld\n", ss(2,10));		/* 1024 */
	printf("%ld\n", ss(8,9));		/* 134217728 */
	printf("%ld\n", ss(99,4));		/* 96059601 */
	printf("%ld\n", ss(45,5));		/* 184528125 */
	printf("Tests for ssm\n");
	printf("%d\n", ssm(2,10, 1000));	/* 24 */
	printf("%d\n", ssm(8,9, 1000));		/* 728 */
	printf("%d\n", ssm(99,4, 100));		/* 1 */
	printf("%d\n", ssm(45,5, 10000));	/* 8125 */
	return 0;
}

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
