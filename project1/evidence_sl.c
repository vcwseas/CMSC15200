#include "raytracer.h"

int main()
{
  printf("%s\n", "testing sl_cons");
  sphere *s1 = sphere_new(vec_new(0.0, 0.0, 0.0), 10.0, rgb_new(0.5, 0.5, 0.5));
  sphere *s2 = sphere_new(vec_new(1.0, 1.0, 1.0), 5.0, rgb_new(0.1, 0.1, 0.1));
  sphere *s3 = sphere_new(vec_new(100.0, 100.0, 100.0), 100.0, rgb_new(0, 0, 0));

  sphere_list *sl = sl_cons(s1, sl_cons(s2, sl_cons(s3, NULL)));
  sl_print(sl);
  printf("%s\n", "testing sl_singleton");
  sphere_list *sl2 = sl_singleton(sphere_dup(s1));
  sl_print(sl2);
  sphere_list *sl3 = sl_cons(sphere_dup(s2), sl_singleton(sphere_dup(s1)));
  sl_print(sl3);

  printf("%s\n", "testing sl_dup");
  sphere_list *sl4 = sl_dup(sl);
  sl_print(sl4);


  printf("%s\n", "FOR VALGRIND TESTING");
  sl_free(sl);
  sl_free(sl2);
  sl_free(sl3);
  sl_free(sl4);
}
