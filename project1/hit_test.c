// Victor Cheung, VCheung
// CMSC 15200, Win 14
// Project 1, hit test

#include "raytracer.h"

hit_test *hit_test_new(double dist, rgb *surf_color, vec *surf_norm)
{
  if (surf_color == NULL || surf_norm == NULL)
  {
    fprintf(stderr, "%s\n", "hit_test_new: parameter is NULL");
    exit(1);
  }
  hit_test *p = malloc(sizeof(hit_test));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "hit_test_new: allocation failure.");
    exit(1);
  }
  p->dist = dist;
  p->surf_color = rgb_dup(surf_color);
  p->surf_norm = surf_norm;
  return p;
}

/* duplicates hit_test in the heap */
hit_test *hit_test_dup(hit_test *t)
{
  if (t == NULL)
  {
    fprintf(stderr, "%s\n", "hit_test_dup: parameter is NULL");
    exit(1);
  }
  hit_test *hdup = malloc(sizeof(hit_test));
  if (hdup == NULL)
  {
    fprintf(stderr, "%s\n", "hit_test_dup: allocation failure.");
    exit(1);
  }
  hdup->dist = t->dist;
  hdup->surf_color = rgb_dup(t->surf_color);
  hdup->surf_norm = vec_dup(t->surf_norm);
  return hdup;
}

/* prints out a hit_test in string format */
void hit_test_print(hit_test *t)
{
  if (t == NULL)
  {
    return;
  }
  printf("HIT_TEST - dist: %.3lf, surf_color: %s, surf_norm: %s - END HIT_TEST STRUCT\n", t->dist, rgb_tos(t->surf_color), vec_tos(t->surf_norm));
  return;
}

/* destructor for a hit_test */
void hit_test_free(hit_test *t)
{
  rgb_free(t->surf_color);
  vec_free(t->surf_norm);
  free(t);
  return;
}




