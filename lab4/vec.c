// Victor Cheung, VCheung
// CMSC 15200, Win 2014
// Lab 4, vectors

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "vec.h"

// vector operations for project 1

/* creates a fresh heap-allocated vector with arguments */
vec *vec_new(double x, double y, double z)
{
  vec *p = malloc(sizeof(vec));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "vec_new: allocation failed.");
    exit(1);
  }
  p->x = x;
  p->y = y;
  p->z = z;
  return p;
}

/* create a fresh vector (new heap allocation) with same components as argument */
vec *vec_dup(vec *v)
{
  vec *p = malloc(sizeof(vec));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "vec_dup: allocation failed.");
    exit(1);
  }
  p->x = v->x;
  p->y = v->y;
  p->z = v->z;
  return p;
}

/* add two vectors (allocate) */
/* (x,y,z) + (X,Y,Z) = (x+X,y+Y,z+Z) */
vec *vec_add(vec *v1, vec *v2)
{
  vec *p = malloc(sizeof(vec));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "vec_add: allocation failed.");
    exit(1);
  }
  p->x = v1->x + v2->x;
  p->y = v1->y + v2->y;
  p->z = v1->z + v2->z;
  return p;
}

/* subtract the second vector from the first (allocate) */
/* (x,y,z) - (X,Y,Z) = (x-X,y-Y,z-Z) */
vec *vec_sub(vec *v1, vec *v2)
{
  vec *p = malloc(sizeof(vec));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "vec_sub: allocation failed.");
    exit(1);
  }
  p->x = v1->x - v2->x;
  p->y = v1->y - v2->y;
  p->z = v1->z - v2->z;
  return p;
}

/* negate a vector (allocate) */
/* -(x,y,z) = (-x,-y,-z) */
vec *vec_neg(vec *v)
{
  vec *p = malloc(sizeof(vec));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "vec_neg: allocation failed.");
    exit(1);
  }
  p->x = - (v->x);
  p->y = - (v->y);
  p->z = - (v->z);
  return p;
}

/* scale the components of a vector by scalar s (allocate) */
/* s(x,y,z) = (sx,sy,sz) */
vec *vec_scale(double s, vec *v)
{
  vec *p = malloc(sizeof(vec));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "vec_scale: allocation failed.");
    exit(1);
  }
  p->x = s * (v->x);
  p->y = s * (v->y);
  p->z = s * (v->z);
  return p;
}

/* compute the dot product of two vectors */
/* (x,y,z) . (X,Y,Z) = xX+yY+zZ */
double vec_dot(vec *v1, vec *v2)
{
  return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

/* compute the magnitude of a vector */
/* the magnitude is the square root of the sum of the squares of the components */
double vec_mag(vec *v)
{
  double sqrsum = v->x * v->x + v->y * v->y + v->z * v->z;
  return sqrt(sqrsum);
}

/* normalize the vector (allocate) */
/* to normalize a vector is to produce a vector pointing in the same direction whose magnitude is 1 */
/* - normalize a vector by scaling by 1 over its magnitude */
/* - if a vector's magnitude is zero, it can't be normalized; simply return it */
vec *vec_norm(vec *v)
{
  double mag;
  if ((mag = vec_mag(v)) == 0)
    return v;
  return vec_scale((1.0 / mag), v);
}

/* produce a string representation of a vector */
char *vec_tos(vec *v)
{
  char buf[128];
  if(v == NULL)
    sprintf(buf, "<>");
  else
  sprintf(buf, "<%lf, %lf, %lf>", v->x, v->y, v->z);
  char *p = strdup(buf);
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "vec_tos: allocation failed.");
    exit(1);
  }
  return p;
}

/* print the string representation of a vector */
void vec_print(vec *v)
{
  if(v == NULL)
    printf("<>");
  else
  printf("<%.3lf, %.3lf, %.3lf>\n", v->x, v->y, v->z);
  return;
}

/* destructor for a vec struct */
void vec_free(vec *v)
{
  free(v);
}


int main()
{
  //test vec_new
  vec *v1 = vec_new(-1.0, -1.0, -1.0);
  vec *v2 = vec_new(10.0, 10.0, 10.0);
  vec *v3 = vec_new(3.0, 4.0, 5.0);
  vec_print(v1);
  vec_print(v2);
  vec_print(v3);
  //test vec_dup
  vec *v4 =  vec_dup(v3);
  vec_print(v4);
  vec_free(v3);
  vec_print(v4);
  v3 = vec_new(3.0, 4.0, 5.0);
  //test vec_add
  vec *v5 = vec_add(v1, v2);
  vec *v6 = vec_add(v1, v3);
  vec_print(v5);
  vec_print(v6);
  //test vec_neg
  vec *v7 = vec_neg(v1);
  vec *v8 = vec_neg(v3);
  vec_print(v7);
  vec_print(v8);
  //test vec_scale
  vec *v9 = vec_scale(10, v1);
  vec *v10 = vec_scale(-1, v1);
  vec_print(v9);
  vec_print(v10);
  //test vec_dot
  printf("%lf\n", vec_dot(v1, v2));
  printf("%lf\n", vec_dot(v2, v3));
  printf("%lf\n", vec_dot(v3, v4));

  //test vec_mag
  printf("%lf\n", vec_mag(v1));
  printf("%lf\n", vec_mag(v2));
  printf("%lf\n", vec_mag(v3));
  //test vec_norm
  printf("%lf\n", vec_mag(vec_norm(v1)));
  printf("%lf\n", vec_mag(vec_norm(v2)));
  printf("%lf\n", vec_mag(vec_norm(v3)));
  //test vec_tos
  printf("%s\n", vec_tos(v1));
  printf("%s\n", vec_tos(v2));
  printf("%s\n", vec_tos(v3));

}
