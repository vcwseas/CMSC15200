// Victor Cheung, vcheung
// CS 152, Winter 2014
// Homework 2, Problem 2
#include <stdlib.h>
#include <stdio.h>


void printBlock(int sl, char c)
{
  int j;
  for (j = 0; j < sl; j++)
    {
       printf("%c", c);
    }
}

void printLine(int sl, int ns, char lc, char dc, int start)
{
  int i, k;
  for (k = 0; k < sl; k++)
  {
      for (i = 0; i < ns; i++)
      {
            char c = start? lc : dc;
            printBlock(sl, c);
            start = !start;
      }
      printf("\n");
      if (ns % 2 == 1)
        start = !start;
  }
}

void printBoard(int sl, int ns, char lc, char dc)
{
  int i;
  for (i = 0; i < ns; i++)
    printLine(sl, ns, lc, dc, i % 2 == 0? 1 : 0);
}

int main(int argc, char *argv[])
{
  printBoard(atoi(argv[1]), atoi(argv[2]), *argv[3], *argv[4]);
}


