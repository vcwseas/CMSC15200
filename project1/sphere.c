// Victor Cheung, VCheung
// CMSC 15200, Win14
// Project 1, Sphere

#include "raytracer.h"

/* constructor for a sphere */
sphere *sphere_new(vec *center, double radius, rgb *color)
{
  sphere *s = malloc(sizeof(sphere));
  if (s == NULL)
  {
    fprintf(stderr, "%s\n", "sphere_new: allocation failed.");
    exit(1);
  }
  s->center = center;
  s->radius = radius;
  s->color = color;
  return s;
}

/* duplicates a sphere to be allocated in the heap */
sphere *sphere_dup(sphere *s)
{
  if (s == NULL)
  {
    return NULL;
  }
  sphere *sdup = malloc(sizeof(sphere));
   if (sdup == NULL)
  {
    fprintf(stderr, "%s\n", "sphere_dup: allocation failed.");
    exit(1);
  }
  sdup->center = vec_dup(s->center);
  sdup->radius = s->radius;
  sdup->color = rgb_dup(s->color);
  return sdup;
}

/* outputs a sphere as a string */
char *sphere_tos(sphere *s)
{
  if (s == NULL)
  {
    return NULL;
  }
  char buf[256];
  sprintf(buf, "SPHERE - center: %s, radius: %.3lf, color: %s", vec_tos(s->center), s->radius, rgb_tos(s->color));
  char *p = strdup(buf);
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "sphere_tos: allocation failed.");
    exit(1);
  }
  return p;
}

/* prints a sphere */
void sphere_print(sphere *s)
{
  if (s == NULL)
  {
    return;
  }
  else
  {
    printf("SPHERE - center: %s, radius: %.3lf, color: %s", vec_tos(s->center), s->radius, rgb_tos(s->color));
  }
  return;
}

/* destructor for a sphere */
void sphere_free(sphere *s)
{
  vec_free(s->center);
  rgb_free(s->color);
  free(s);
}
