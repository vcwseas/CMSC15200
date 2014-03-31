#include "raytracer.h"

int main()
{
  printf("%s\n", "testing sphere_new");
  sphere *s1 = sphere_new(vec_new(0.0, 0.0, 0.0), 10.0, rgb_new(0.5, 0.5, 0.5));
  sphere *s2 = sphere_new(vec_new(1.0, 1.0, 1.0), 10.0, rgb_new(0.2, 0.3, 0.4));
  sphere_print(s1);
  sphere_print(s2);
  printf("%s\n", "testing sphere_dup");
  sphere *s3 = sphere_dup(s1);
  sphere *s4 = sphere_dup(s2);
  sphere_free(s1);
  sphere_free(s2);
  sphere_print(s3);
  sphere_print(s4);
  s1 = sphere_dup(s3);
  s2 = sphere_dup(s4);
  printf("%s\n", "testing sphere_tos");
  char *p = sphere_tos(s3);
  char *p2 = sphere_tos(s4);
  printf("%s\n", p);
  printf("%s\n", p2);
}
