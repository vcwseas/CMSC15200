/* testing ray */

#include "raytracer.h"

int main()
{
  printf("%s\n", "testing ray_new");
  ray *r1 = ray_new(vec_new(0.0, 0.0, -1.0), vec_new(0.0, 0.0, 1.0));
  ray_print(r1);

  printf("%s\n", "testing ray_dup");
  ray *r2 = ray_dup(r1);
  ray_free(r1);
  ray_print(r2);
  r1 = ray_dup(r2);
  ray_print(r1);

  printf("%s\n", "testing ray_position");
  vec_print(ray_position(r1, 10));
  vec_print(ray_position(r1, 0.5));

  printf("%s\n", "testing ray_tos");
  printf("%s", ray_tos(r1));
  printf("%s", ray_tos(r2));

}
