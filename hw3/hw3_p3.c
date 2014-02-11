//Victor Cheung, vcheung
//CS152, Win14
//Homework 3, Problem 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct rgbf {
  float r;
  float g;
  float b;
};
typedef struct rgbf rgbf;

//constructor for an rgbf
//outputs an rgbf pointer
rgbf *rgbf_new(float r, float g, float b)
{
  if (r < 0.0 || 1.0 < r || g < 0.0
    || 1.0 < g || b < 0.0 || 1.0 < b)
  {
    fprintf(stderr, "%s\n", "rgbf_new: arg out of bounds");
    exit(1);
  }
  rgbf *p = malloc(sizeof(rgbf));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "rgbf: NULL POINTER EXCEPTION");
    exit(1);
  }
  p->r = r;
  p->g = g;
  p->b = b;
  return p;
}

//displays rgbf as f1, f2, f3
void rgbf_show(rgbf *c)
{
  printf("%f, %f, %f\n", c->r, c->g, c->b);
}

//destructors for rgbf
void rgbf_free(rgbf *c)
{
  free(c);
}

//produces the negative of an rgbf
//returns a pointer to the new rgbf
rgbf *rgbf_negative(rgbf *c)
{
  rgbf *p = malloc(sizeof(rgbf));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "rgbf_negative: NULL POINTER EXCEPTION");
    exit(1);
  }
  p->r = 1.0f - (c->r);
  p->g = 1.0f - (c->g);
  p->b = 1.0f - (c->b);
  return p;
}

int main(int argc, char **argv)
{
  rgbf *p = rgbf_new(atof(argv[1]), atof(argv[2]), atof(argv[3]));
  rgbf_show(p);
  rgbf_show(rgbf_negative(p));
  rgbf_free(p);
  return 0;
}
