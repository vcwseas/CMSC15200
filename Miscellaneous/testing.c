#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct point {
  double x;
  double y;
  double z;
  double k;
};

int *fromto(int lo, int hi)
{
  int len = hi - lo + 1;
  int *p = malloc(len * sizeof(struct point));
  struct point *po = p;
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "SHIT's FUCKED UP");
    exit(1);
  }
  int i;
  for (i = 0; i < len; i++)
  {
    p[i] = i + lo;
  }
  po->x = 1.0;
  return p;
}

void show(int *p, int len)
{
  int i;
  for (i = 0; i < len; i++)
    printf("%d ", p[i]);
  printf("\n");
}

typedef union fun fun;
union fun {
  char c;
  long l;
  unsigned int i;
};


int main(int argc, char **argv)
{
  fun f = {.i = -100};
  printf("%c\n", f.c);
  printf("%d\n", f.i);
  printf("%ld\n", f.l);

}
