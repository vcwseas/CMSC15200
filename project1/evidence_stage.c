#include "raytracer.h"

int main()
{
  printf("%s\n", "testing stage_new");
  camera *c1 = camera_new(vec_new(0.0, 0.0, 1.0), 10, 10);

  sphere *s1 = sphere_new(vec_new(0.0, 0.0, 0.0), 10.0, rgb_new(0.5, 0.5, 0.5));
  sphere *s2 = sphere_new(vec_new(1.0, 1.0, 1.0), 5.0, rgb_new(0.1, 0.1, 0.1));
  sphere *s3 = sphere_new(vec_new(100.0, 100.0, 100.0), 100.0, rgb_new(0, 0, 0));
  sphere_list *sl = sl_cons(s1, sl_cons(s2, sl_cons(s3, NULL)));

  light *l = light_new(vec_new(0.0, 0.0, 1.0), rgb_new(0.0, 0.5, 1.0));
  rgb *amb = rgb_new(0.5, 0.5, 0.5);
  rgb *bg = rgb_new(1.0, 1.0, 1.0);
  scene *sc = scene_new(bg, sl, l, amb);
  stage *st1 = stage_new(c1, sc);
  stage_print(st1);

  printf("%s\n", "testing stage_dup");
  stage *st2 = stage_dup(st1);
  stage_free(st1);
  stage_print(st2);

  printf("%s\n", "testing get_stage");
  stage *st3 = get_stage("hello");
  stage_print(st3);

  printf("%s\n", "VALGRIND TESTING");
  stage_free(st2);



}
