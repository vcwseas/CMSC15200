//euler problem10

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int prime(unsigned long int n)
{
  if (n < 2)
    return 1;
  else if (n == 2 || n == 3)
    return 1;
  else if (n % 2 == 0 || n % 3 == 0)
    return 0;
  else
  {
    unsigned long max = sqrt(n), div = 5;
    while (div <= max)
    {
      if (n % div == 0 || n % (div + 2) == 0)
        return 0;
      div += 6;
    }
  }

  return 1;
}

//add primes up to n
unsigned long int addPrimes(unsigned long int n)
{
  if (n < 2)
    return 0;
  else if (n < 4)
    return 2;
  else if (n < 6)
    return 5;
  else
  {
    unsigned long int i, sum = 5;
    for (i = 5; i < n; i+=2)
      if (prime(i))
        sum+=i;
    return sum;
  }
}

int main()
{
  printf("%lu\n", addPrimes(2000000));
}
