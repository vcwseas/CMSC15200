#include "raytracer.h"

rgb compute_surf(vec center, vec loc, timestamp t)
{
  return rgb_expr(sin(loc.x*t), sin(loc.y*t), sin(loc.z*t));
}


rgb compute_shine(timestamp t)
{
  return rgb_expr(.4, .4, .4);
}

frame compute_frame(timestamp t)
{
  frame f;
  f.ts = t;

  f.bg = rgb_expr(.1, .1, .4);

  fsphere sph0 = {vec_expr(.67, 0, 4), 0.67, compute_surf, compute_shine};
  fsphere_list *spheres = fsl_cons(sph0, NULL);
  f.spheres = spheres;

  vec ldir = vec_norm(vec_expr(-3,1,-1));
  light lt = {ldir,{1,1,1}};
  f.light = lt;

  rgb amb = rgb_expr(.33, .33, .33);
  f.amb = amb;

  return f;
}

fstage get_fstage(char *fut)
{
  fstage fst;
  camera test_camera_1 = {{0,0,-5},288,512};
  /* n.b. 16x9 is the cinematic widescreen ratio :-) */
  fst.c = test_camera_1;
  fst.compute_frame = compute_frame;
  fst.n_frames = 100;
  return fst;
}


