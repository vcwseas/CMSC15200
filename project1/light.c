// Victor Cheung, VCheung
// CMSC 15200, Win 2014
// Lab 4, light

#include "raytracer.h"

/* constructor for a light struct */
light *light_new(vec *direction, rgb *color)
{
  if (direction == NULL || color == NULL)
  {
    fprintf(stderr, "%s\n", "light_new: parameters are NULL");
    exit(1);
  }
  light *l = malloc(sizeof(light));
  if (l == NULL)
  {
    fprintf(stderr, "%s\n", "light_new: allocation failure.");
    exit(1);
  }
  l->direction = direction;
  l->color = color;
  return l;
}


/* allocates a new light on the heap */
light *light_dup(light *l)
{
  if (l == NULL)
  {
    fprintf(stderr, "%s\n", "light_dup: parameter is NULL");
    exit(1);
  }
  light *ldup = malloc(sizeof(light));
  if (ldup == NULL)
  {
    fprintf(stderr, "%s\n", "light_dup: allocation failure.");
    exit(1);
  }
  ldup->direction = vec_dup(l->direction);
  ldup->color = rgb_dup(l->color);
  return ldup;
}

/* prints out light in string format */
void light_print(light *l)
{
  if (l == NULL)
  {
    fprintf(stderr, "%s\n", "light_print: paramter is NULL");
    exit(1);
  }
  printf("LIGHT - direction: %s, color: %s - END LIGHT STRUCT\n", vec_tos(l->direction), rgb_tos(l->color));
  return;
}

/* destructor for a light */
void light_free(light *l)
{
  vec_free(l->direction);
  rgb_free(l->color);
  free(l);
}



