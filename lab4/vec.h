typedef struct vec {
  double x;
  double y;
  double z;
} vec;

/* === vector operations === */

vec *vec_new(double x, double y, double z);

/* create a fresh vector (new heap allocation) with same components as argument */
vec *vec_dup(vec *v);

/* add two vectors (allocate) */
/* (x,y,z) + (X,Y,Z) = (x+X,y+Y,z+Z) */
vec *vec_add(vec *v1, vec *v2);

/* subtract the second vector from the first (allocate) */
/* (x,y,z) - (X,Y,Z) = (x-X,y-Y,z-Z) */
vec *vec_sub(vec *v1, vec *v2);

/* negate a vector (allocate) */
/* -(x,y,z) = (-x,-y,-z) */
vec *vec_neg(vec *v);

/* scale the components of a vector by scalar s (allocate) */
/* s(x,y,z) = (sx,sy,sz) */
vec *vec_scale(double s, vec *v);

/* compute the dot product of two vectors */
/* (x,y,z) . (X,Y,Z) = xX+yY+zZ */
double vec_dot(vec *v1, vec *v2);

/* compute the magnitude of a vector */
/* the magnitude is the square root of the sum of the squares of the components */
double vec_mag(vec *v);

/* normalize the vector (allocate) */
/* to normalize a vector is to produce a vector pointing in the same direction whose magnitude is 1 */
/* - normalize a vector by scaling by 1 over its magnitude */
/* - if a vector's magnitude is zero, it can't be normalized; simply return it */
vec *vec_norm(vec *v);

/* produce a string representation of a vector */
char *vec_tos(vec *v);

/* print the string representation of a vector */
void vec_print(vec *v);

void vec_free(vec *v);
