#include "raytracer.h"

stage get_stage(char *fut)
{
  camera test_camera_1 = {{0,0,-5},288,512};
  /* n.b. 16x9 is the cinematic widescreen ratio :-) */
  sphere sph0 = {{0.67,0,4},0.67,{0.4,0.6,1.0},{1.0, 1.0, 1.0}};
  sphere_list *spheres = sl_singleton(sph0);
  vec ldir = vec_norm(vec_expr(-3,1,-1));
  light lt = {ldir,{1,1,1}};
  scene test_scene_1 = {{0.1,0.1,0.4},spheres,lt,{0.33,0.33,0.33}};
  stage g = {test_camera_1, test_scene_1};
  return g;
}
