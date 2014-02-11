//Euler p9

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int special_triplet()
{
  int max = 100, tmp;
  int m, n;
  for (m = 1; m < max; m++)
    for (n = 1; n < max; n++)
      if (n >= m) break;
      else if ((tmp = m * m + m * n) == 500)
        return product(m,n);
      else if (tmp > 500)
      {
        break;
      }
}

int product(int m, int n)
{
  return (m * m - n * n) * (2 * m * n) * (m * m + n * n);
}

int main()
{
  printf("%d\n", special_triplet());
}
