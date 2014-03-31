// Victor Cheung, VCheung
// CMSC 15200, Win 14
// Project 1, Rays

#include "raytracer.h"

/* constructor for a ray */
ray *ray_new(vec *origin, vec *direction)
{
  ray *p = malloc(sizeof(ray));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "ray_new: allocation error");
    exit(1);
  }
  p->origin = origin;
  p->direction = direction;
  return p;
}

/* duplicates and returns a new ray in the heap */
ray *ray_dup(ray *r)
{
  if (r == NULL)
  {
    return NULL;
  }
  ray *p = malloc(sizeof(ray));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "ray_new: allocation error");
    exit(1);
  }
  p->origin = vec_dup(r->origin);
  p->direction = vec_dup(r->direction);
  return p;
}

/* finds the position of a ray at some time */
vec *ray_position(ray *r, double time)
{
  vec *d = vec_norm(r->direction);
  vec *w = vec_scale(time, d);
  vec *result = vec_add(r->origin, w);
  vec_free(w);
  vec_free(d);
  return result;
}

/* returns a string representing a ray */
char *ray_tos(ray *r)
{
  char buf[256];
  if (r == NULL)
  {
    return NULL;
  }
  sprintf(buf, "RAY - origin: %s, direction: %s\n", vec_tos(r->origin), vec_tos(r->direction));
  char *p = strdup(buf);
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "ray_tos: allocation failed.");
    exit(1);
  }
  return p;
}

/*prints out a representation of the ray */
void ray_print(ray *r)
{
  if (r == NULL)
    return;
  printf("RAY - origin: %s, direction: %s\n", vec_tos(r->origin), vec_tos(r->direction));
  return;
}


/* destructor for a ray */
void ray_free(ray *r)
{
  vec_free(r->origin);
  vec_free(r->direction);
  free(r);
  return;
}


