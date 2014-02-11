
//Victor Cheung, Vcheung
//CS152, Win14
//Homework 3, Problem 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//displays an array in format [a1, a2, a3, a4... an]
//returns void
void ia_show(unsigned long a[], int len, int newline)
{
  int i;
  printf("[");
  for (i = 0; i < len; i++)
  {
    if (i == len - 1)
      printf("%ld", a[i]);
    else
      printf("%ld, ", a[i]);
  }
  printf("]");
  if (newline)
    printf("\n");
}

//creates a dynamic array on the heap storing the first n powers of
// some integer m.
//returns the pointer to the array.
unsigned long int *first_n_powers(unsigned int m, unsigned int n)
{
  unsigned long int i, *p = malloc(n * sizeof(unsigned long int));
  for(i = 0; i < n; i++)
  {
    p[i] = pow(m, i);
  }
  return p;
}

// manual testing here; enter m first and n second.
int main(int argc, char **argv)
{
  unsigned long *p = first_n_powers(atoi(argv[1]), atoi(argv[2]));
  ia_show(p, atoi(argv[2]), 1);
  free(p);
}
