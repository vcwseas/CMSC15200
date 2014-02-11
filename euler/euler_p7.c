//Euler P7
//Victor Cheung

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

//find the pos'th prime
unsigned long int count_prime(unsigned long int pos)
{
  unsigned long int i = 2, count = 1;
  while (count < pos)
  {
    if (prime(++i))
      count++;
  }

  return i;
}

int main(int argc, char **argv)
{
  printf("%lu\n", count_prime(atoi(argv[1])));
  return 0;
}
