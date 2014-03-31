typedef struct rgb {
  /* each value must be on interval [0,1] */
  double r;
  double g;
  double b;
} rgb;
/* === rgb operations === */

rgb *rgb_new(double r, double g, double b);

rgb *rgb_dup(rgb *c);

/* multiply the components or two rgbs (allocate) */
/* (r,g,b) * (R,G,B) = (rR,gG,bB) */
rgb *rgb_modulate(rgb *c1, rgb *c2);

/* scale each component by given scalar, but don't allow */
/* any component in the result to fall outside [0,1] (allocate) */
rgb *rgb_scale(double s, rgb *c);

/* add components of colors (allocate) */
/* but don't allow any component in the result to exceed 1 */
rgb *rgb_add(rgb *c1, rgb *c2);

char *rgb_tos(rgb *c);

void rgb_print(rgb *c);

void rgb_free(rgb *c);

/* print three integer values on [0,255] with spaces in between and a newline */
/* for example, printing the bytes for rgb (1.0,1.0,0.0) should print */
/* "255 255 0\n" */
void rgb_print_bytes(rgb *c);
