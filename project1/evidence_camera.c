#include "raytracer.h"

int main()
{
  fprintf(stderr, "%s\n", "testing camera_new");
  camera *c1 = camera_new(vec_new(0.0, 0.0, 1.0), 10, 10);
  camera_print(c1);
  fprintf(stderr, "%s\n", "testing camera_dup");
  camera *c2 = camera_dup(c1);
  camera_free(c1);
  camera_print(c2);
  c1 = camera_dup(c2);
  fprintf(stderr, "%s\n", "VALGRIND TESTING");
  camera_free(c1);
  camera_free(c2);

}
