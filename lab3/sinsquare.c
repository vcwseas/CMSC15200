// Victor Cheung, vcheung
// CS 152, Winter 2014
// Lab3
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void printPPM(int side, double rs, double gs, double bs)
{
  double i, j, distance, sinr, sing, sinb;
  double center = side / 2.0;
  int r, g, b;
  printf("P3\n%d %d\n255\n", side, side);
  for (i = 0; i < side; i++)
  {
    for (j = 0; j < side; j++)
    {
      distance = sqrt(  pow( fabs(i - center), 2)
        + pow( fabs(j - center), 2 ));
      sinr = sin(distance * rs);
      sing = sin(distance * gs);
      sinb = sin(distance * bs);
      r = (int) (((sinr + 1.0) / 2.0) * 255.0);
      g = (int) (((sing + 1.0) / 2.0) * 255.0);
      b = (int) (((sinb + 1.0) / 2.0) * 255.0);
      printf("%d %d %d\n", r, g, b);
    }
  }
}

int main(int argc, char **argv)
{
  //initialize default values
  int side = 480;
  double rs = 1.0;
  double gs = 1.0;
  double bs = 1.0;

  int i;
  for(i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-r") == 0)
      rs  = atof(argv[i+1]);
    else if (strcmp(argv[i], "-g") == 0)
      gs  = atof(argv[i+1]);
    else if (strcmp(argv[i], "-b") == 0)
      bs  = atof(argv[i+1]);
    else if (strcmp(argv[i], "-s") == 0)
      side  = atoi(argv[i+1]);
  }

  printPPM(side, rs, gs, bs);
  return 0;
}
