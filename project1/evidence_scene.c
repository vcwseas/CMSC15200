#include "raytracer.h"

int main()
{
  printf("%s\n", "testing scene_new");
  rgb *r = rgb_new(1.0, 0.5, 0.0);
  sphere *s = sphere_new(vec_new(0.0, 0.0, 0.0), 10.0, rgb_new(1.0, 1.0, 1.0));
  sphere_list *sl = sl_singleton(s);
  light *l = light_new(vec_new(0.0, 0.0, 1.0), rgb_new(0.0, 0.5, 1.0));
  rgb *amb = rgb_new(0.5, 0.5, 0.5);
  scene *s1 = scene_new(r, sl, l, amb);
  scene_print(s1);

  printf("VALGRIND TESTING\n");
  scene_free(s1);
}
