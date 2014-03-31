// Victor Cheung, VCheung
// CMSC15200, Win14
// Lab4, rgb

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "rgb.h"

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
  rgb *p = malloc(sizeof(rgb));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_dup: allocation failed");
    exit(1);
  }
  p->r = c->r;
  p->g = c->g;
  p->b = c->b;
  return p;
}

/* multiply the components or two rgbs (allocate) */
/* (r,g,b) * (R,G,B) = (rR,gG,bB) */
rgb *rgb_modulate(rgb *c1, rgb *c2)
{
  rgb *p = malloc(sizeof(rgb));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_modulate: allocation failed");
    exit(1);
  }
  p->r = c1->r * c2->r;
  p->g = c1->g * c2->g;
  p->b = c1->b * c2->b;
  return p;
}

/* scale each component by given scalar, but don't allow */
/* any component in the result to fall outside [0,1] (allocate) */
rgb *rgb_scale(double s, rgb *c)
{
  rgb *p = malloc(sizeof(rgb));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_scale: allocation failed");
    exit(1);
  }
  p->r = s * c->r;
  p->g = s * c->g;
  p->b = s * c->b;
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
  rgb *p = malloc(sizeof(rgb));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "rgb_add: allocation failed");
    exit(1);
  }
  p->r = c1->r + c2->r;
  p->g = c1->g + c2->g;
  p->b = c1->b + c2->b;
  if (rgb_valid(p))
  {
    return p;
  } else {
    fprintf(stderr, "%s\n", "rgb_add: added values exceed acceptable range.");
    exit(1);
  }
}

/* converts rgb to a string */
char *rgb_tos(rgb *c)
{
  char buf[256];
  if (c == NULL)
  {
    return NULL;
  }
  sprintf(buf, "(r: %.3lf, g:%.3lf, b:%.3lf)\n", c->r, c->g, c->b);
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
    printf("(r: %.3lf, g:%.3lf, b:%.3lf)\n", c->r, c->g, c->b);
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

int main()
{
  //test rgb_new
  rgb *c1 = rgb_new(1.0, 1.0, 1.0);
  rgb *c2 = rgb_new(0.0, 0.0, 0.0);
  rgb *c3 = rgb_new(0.5, 0.5, 0.5);
  rgb_print(c1);
  rgb_print(c2);
  rgb_print(c3);
  rgb_print_bytes(c1);
  rgb_print_bytes(c2);
  rgb_print_bytes(c3);
  //test rgb_dup
  rgb *c4 = rgb_dup(c1);
  rgb_free(c1);
  rgb_print(c4);
  rgb_print_bytes(c4);
  c1 = rgb_dup(c4);
  //test rgb_module
  rgb *c5 = rgb_modulate(c1, c3);
  rgb *c6 = rgb_modulate(c2, c3);
  rgb_print(c5);
  rgb_print(c6);
  rgb_print_bytes(c5);
  rgb_print_bytes(c6);
  //test rgb_scale
  rgb *c7 = rgb_scale(0.7, c1);
  rgb *c8 = rgb_scale(0.25, c3);
  rgb_print(c7);
  rgb_print(c8);
  rgb_print_bytes(c7);
  rgb_print_bytes(c8);
  //test rgb_add
  rgb *c9 = rgb_add(c1, c2);
  rgb *c10 = rgb_add(c3, c8);
  rgb_print(c9);
  rgb_print(c10);
  rgb_print_bytes(c9);
  rgb_print_bytes(c10);
  //test rgb_tos
  printf("%s", rgb_tos(c1));
  printf("%s", rgb_tos(c2));
  printf("%s", rgb_tos(c3));
  //test rgb_printbytes
  rgb_print_bytes(rgb_new(1.0, 1.0, 0));

}
