// Victor Cheung, VCheung
// CMSC 15200, Win 2014
// Lab 4, vectors

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "raytracer.h"

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
  if (v == NULL)
  {
    fprintf(stderr, "%s\n", "vec_dup: parameter is NULL.");
    exit(1);
  }
  return vec_new(v->x, v->y, v->z);
}

/* add two vectors (allocate) */
/* (x,y,z) + (X,Y,Z) = (x+X,y+Y,z+Z) */
vec *vec_add(vec *v1, vec *v2)
{

  if (v1 == NULL || v2 == NULL)
  {
    fprintf(stderr, "%s\n", "vec_add: parameter is NULL");
    exit(1);
  }
  return vec_new(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

/* subtract the second vector from the first (allocate) */
/* (x,y,z) - (X,Y,Z) = (x-X,y-Y,z-Z) */
vec *vec_sub(vec *v1, vec *v2)
{
  if (v1 == NULL || v2 == NULL)
  {
    fprintf(stderr, "%s\n", "vec_sub: parameter is NULL");
    exit(1);
  }
  return vec_new(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}

/* negate a vector (allocate) */
/* -(x,y,z) = (-x,-y,-z) */
vec *vec_neg(vec *v)
{
  if (v == NULL)
  {
    fprintf(stderr, "%s\n", "vec_neg: parameter is NULL");
    exit(1);
  }
  return vec_new(- (v->x), - (v->y), - (v->z));
}

/* scale the components of a vector by scalar s (allocate) */
/* s(x,y,z) = (sx,sy,sz) */
vec *vec_scale(double s, vec *v)
{
  if (v == NULL)
  {
    fprintf(stderr, "%s\n", "vec_scale: parameter is NULL");
    exit(1);
  }
  return vec_new(s * (v->x), s * (v->y), s * (v->z));
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
  if (fabs((mag = vec_mag(v))) <  0.00001)
    return v;
  return vec_scale((1.0 / mag), v);
}

/* produce a string representation of a vector */
char *vec_tos(vec *v)
{
  char buf[128];
  if(v == NULL)
  {
    return NULL;
  }
  sprintf(buf, "VEC - <%.3lf, %.3lf, %.3lf>", v->x, v->y, v->z);
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
  {
    printf("<>");
  }
  else
  {
    printf("VEC - <%.3lf, %.3lf, %.3lf>\n", v->x, v->y, v->z);
  }
  return;
}

/* destructor for a vec struct */
void vec_free(vec *v)
{
  free(v);
}


