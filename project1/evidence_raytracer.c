#include "raytracer.h"

int main()
{
  printf("%s\n", "testing logical_loc");
  camera *c = camera_new(vec_new(0.0, 0.0, -1.0), 14, 10);
  vec *v = vec_new(9,13,0);
  vec_print(logical_loc(c, v));

}
