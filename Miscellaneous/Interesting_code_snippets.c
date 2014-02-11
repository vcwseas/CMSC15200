//Interesting Code Snippets

#include <stdlib.h>
#include <stdio.h>

// struct point
// {
//   double x;
//   double y;
// };
// typedef struct point poi;

// int main (int argc, char **argv)
// {
//   poi *p = malloc(sizeof(poi));
//   poi pi = {.y = 2, .x = 1};
//   memcpy(p, &pi, sizeof(pi));
//   printf(" The point is (%f, %f) \n", p->x, p->y );
// }


#include <stdio.h>

void measure_array(int a[])
{
  printf("measure_array: the size of a in bytes is %lu\n", sizeof(a));
}

int main()
{
  int a[6] = {1,1,1,1,1,1};
  printf("main: the size of a in bytes is %lu\n", sizeof(a));
  measure_array(a);
  return 0;
}
