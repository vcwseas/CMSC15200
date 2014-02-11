// Victor Cheung, vcheung
// CS 152, Winter 2014
// Homework 2, Problem 3

#include <stdio.h>
#include <math.h>

void printPPM()
{
  int side = 480;
  double i, j, distance, sinv;
  int b;
  printf("P3\n480 480\n255\n");
  for (i = 0; i < side; i++)
  {
    for (j = 0; j < side; j++)
    {
      distance = sqrt(  pow( fabs(i - 240), 2)
        + pow( fabs(j - 240), 2 ));
      sinv = sin(distance);
      b = (int) (((sinv + 1.0) / 2.0) * 255.0);
      printf("0 0 %d\n", b);
    }
  }
}

int main()
{
  printPPM();
  return 0;
}
