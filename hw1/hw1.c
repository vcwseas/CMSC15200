/* Victor Cheung, vcheung */
/* CS 152, Winter 2014 */
/* Homework 1 */

#include <stdio.h>
#include <math.h>


/*
 *
 *
 * problem 1
 *
 *
 */
// recursive implementation
// unsigned int gcd(unsigned int a, unsigned int b)
// {
// 	if (b > a)
// 		return gcd(b, a);
// 	else if (b)
// 		return gcd(b, a % b);
// 	else
// 		return a;
// }

unsigned int gcd(unsigned int a, unsigned int b)
{
	if (b > a)
		return gcd(b, a);

	unsigned int temp;
	while (b)
	{
		temp = a;
		a = b;
		b = temp % b;
	}
	return a;
}

/*
 *
 *
 * problem 2
 *
 *
 */
double area_pipe(double inner_radius, double length, double thickness)
{
	double outer_radius = inner_radius + thickness;
	double ir2 = inner_radius * inner_radius;
	double or2 = outer_radius * outer_radius;

	return (2 * M_PI * inner_radius * length)
		+  (2 * M_PI * outer_radius * length)
		+  2 * (or2 * M_PI - ir2 * M_PI);
}

/*
 *
 *
 * problem 3
 *
 *
 */

int adj(unsigned int m, unsigned int y)
{
	int leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	switch (m)
	{
		case 1: return leap ? 0 : 1;
		case 2: return leap ? 3 : 4;
		case 3: return 4;
		case 4: return 0;
		case 5: return 2;
		case 6: return 5;
		case 7: return 0;
		case 8: return 3;
		case 9: return 6;
		case 10: return 1;
		case 11: return 4;
		case 12: return 6;
	}
}

int dow(unsigned int d, unsigned int m, unsigned int y)
{
	return ((y - 1900) + adj(m, y) + d + y/4) % 7;
}



/*
 *
 *
 * problem 4
 *
 *
 */

 int sumDigitsDoubled(int n)
{
	n = n * 2;
	return n % 10 + (n / 10) % 10;
}


int luhnAux(unsigned long int num, int check, int sum, int d)
{

	if (num == 0)
		return ((10 - (sum % 10))) % 10 == check;
	else
		return luhnAux(num / 10, check,
			sum + (d ? sumDigitsDoubled(num % 10) : num % 10), !d);
}

int luhn(unsigned long int num)
{
	return luhnAux(num / 10, num % 10, 0, 1);
}

/*
 *
 *
 *
 * Main
 *
 */


int main()
{
	printf("Tests for problem 1\n");
	printf("%d\n", gcd(50,24)); 	/* 2 */
	printf("%d\n", gcd(44,22)); 	/* 22 */
	printf("%d\n", gcd(5678, 56)); 	/* 2 */
	printf("%d\n", gcd(23, 69) ); 	/* 23 */
	printf("%d\n", gcd(1024, 1020304)); 	/* 16 */
	printf("%d\n", gcd(512, 1024)); 	/* 512 */
	printf("\n");
	printf("Tests for problem 2\n");
	printf("%f\n", area_pipe(12, 12, 2)); 	/* 502.655 */
	printf("%f\n", area_pipe(100, 2, 12)); 	/* 18648.49399 */
	printf("\n");
	printf("Tests for problem 3 \nin day-month-year format.\n");
	printf("%d-%d-%d is the %d day of the week\n", 9, 12, 1995, dow(9, 12 , 1995));
	printf("%d-%d-%d is the %d day of the week\n", 29, 2, 1908, dow(29, 2 , 1908));
	printf("%d-%d-%d is the %d day of the week\n", 23, 12, 1908, dow(23, 12 , 1908));
	printf("%d-%d-%d is the %d day of the week\n", 1, 6, 1919, dow(1, 6 , 1919));
	printf("\n");
	printf("Tests for problem 4\n");
	printf("%d\n", luhn(18929)); 			/* true */
	printf("%d\n", luhn(49927398716)); 		/* true */
	printf("%d\n", luhn(378282246310005)); 	/* true */
	printf("%d\n", luhn(1231241241232) );	/* false */
	printf("%d\n", luhn(1230) );	/* true */
	printf("%d\n", luhn(26));
	return 0;
}

