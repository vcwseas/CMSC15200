// Victor Cheung, VCheung
// CMSC15200, Win14
// Lab4, rgb

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "raytracer.h"

/* checks whether an rgb struct is valid; it's valid if it's not null and has valued in [0,1]; it's invalid otherwise*/
int rgb_valid(rgb *c)
{
  if (c == NULL)
    return 0;
  else
    return c->r <= 1 && c->r >= 0 && c->g <= 1 && c->g >= 0 && c->b <= 1 && c->b >= 0;
}

/* constructor for an rgb struct */
rgb *rgb_new(double r, double g, double b)
{
  rgb *p = malloc(sizeof(rgb));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_new: allocation failed");
    exit(1);
  }
  p->r = r;
  p->g = g;
  p->b = b;
  return p;
}

/* duplicates an rgb struct on the stack */
rgb *rgb_dup(rgb *c)
{
  if (c == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_dup: parameter is NULL");
    exit(1);
  }
  return rgb_new(c->r, c->g, c->b);
}

/* multiply the components or two rgbs (allocate) */
/* (r,g,b) * (R,G,B) = (rR,gG,bB) */
rgb *rgb_modulate(rgb *c1, rgb *c2)
{
  if (c1 == NULL || c2 == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_modulate: parameter is NULL");
    exit(1);
  }
  return rgb_new(c1->r * c2->r, c1->g * c2->g, c1->b * c2->b);
}

/* scale each component by given scalar, but don't allow */
/* any component in the result to fall outside [0,1] (allocate) */
rgb *rgb_scale(double s, rgb *c)
{
  if (c == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_scale: parameter is NULL.");
    exit(1);
  }
  rgb *p = rgb_new(s * c->r, s * c->g, s * c->b);
  if (rgb_valid(p))
  {
    return p;
  } else {
    fprintf(stderr, "%s\n", "rgb_scale: scaled values exceed acceptable range.");
    exit(1);
  }
}

/* add components of colors (allocate) */
/* but don't allow any component in the result to exceed 1 */
rgb *rgb_add(rgb *c1, rgb *c2)
{
  if (c1 == NULL || c2 == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_add: parameter is NULL");
    exit(1);
  }

  //we clamp the maximum component value at 1
  double r = c1->r + c2->r;
  r = r > 1 ? 1 : r;

  double g = c1->g + c2->g;
  g = g > 1 ? 1 : g;

  double b = c1->b + c2->b;
  b = b > 1 ? 1 : b;

  rgb *p = rgb_new(r, g, b);
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_add: allocation failed.");
    exit(1);
  }
  return p;
}

/* converts rgb to a string */
char *rgb_tos(rgb *c)
{
  char buf[256];
  if (c == NULL)
  {
    return NULL;
  }
  sprintf(buf, "(RGB - r: %.3lf, g:%.3lf, b:%.3lf)\n", c->r, c->g, c->b);
  char *p = strdup(buf);
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_tos: allocation failed");
    exit(1);
  }
  return p;
}
/* prints an rgb struct */
void rgb_print(rgb *c)
{
  if (c == NULL)
    return;
  else
  {
    printf("(RGB - r: %.3lf, g:%.3lf, b:%.3lf)\n", c->r, c->g, c->b);
  }
  return;
}
/* destructor for an rgb */
void rgb_free(rgb *c)
{
  free(c);
}

/* print three integer values on [0,255] with spaces in between and a newline */
/* for example, printing the bytes for rgb (1.0,1.0,0.0) should print */
/* "255 255 0\n" */
void rgb_print_bytes(rgb *c)
{
  if (c == NULL)
  {
    return;
  }
  else
  {
    printf("%d, %d, %d\n", (int) (c->r * 255), (int) (c->g * 255), (int) (c->b * 255));
  }
}


