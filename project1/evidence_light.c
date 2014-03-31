#include "raytracer.h"

int main()
{
  printf("%s\n", "testing light_new");
  light *l1 = light_new(vec_new(0.0, 0.0, 1.0), rgb_new(1.0, 1.0, 1.0));
  light_print(l1);
  printf("%s\n", "testing light_dup");
  light *l2 = light_dup(l1);
  light_free(l1);
  light_print(l2);
  l1 = light_dup(l2);
  printf("%s\n", "VALGRIND TESTING");
  light_free(l1);
  light_free(l2);
}
