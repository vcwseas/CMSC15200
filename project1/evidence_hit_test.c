#include "raytracer.h"

int main()
{
  printf("%s\n", "testing hit_test_new");
  rgb *r = rgb_new(0.0, 0.5, 1.0);
  vec *v = vec_new(0.0, 0.0, 1.0);
  hit_test *h = hit_test_new(10.0, r, v);
  hit_test_print(h);

  printf("%s\n", "testing hit_test_dup");
  hit_test *h2 = hit_test_dup(h);
  hit_test_free(h);
  hit_test_print(h2);

  printf("%s\n", "VALGRIND TESTING");
  hit_test_free(h2);
}
