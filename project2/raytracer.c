#include "raytracer.h"
//When I wrote this only God and I knew what I was doing;
//now only God knows.

double double_max(double a, double b)
{
  return a>b ? a : b;
}

hit_test intersect(ray r, sphere s)
{
  hit_test result = {0}; /* {0} to quiet the compiler */
  vec sc = s.center;
  double sr = s.radius;
  vec A = vec_sub(r.origin, sc);
  double B = vec_dot(A, r.direction);
  double C = vec_dot(A, A) - (sr * sr);
  double D = (B * B) - C;
  double t = (-B - sqrt(D));
  result.miss = 1;
  if (D > 0 && t > 0) {
    result.miss = 0;
    result.dist = t;
    result.surf = s.surf;
    result.shine = s.shine;
    result.surf_norm = vec_norm(vec_sub(ray_position(r,t),sc));
  }
  return result;
}

int shadow(vec pt, light l, sphere_list *ss)
{
  vec nudge = vec_scale(0.0001, l.direction);
  vec lifted = vec_add(pt, nudge);
  ray test_ray = {lifted, l.direction};
  while (ss!=NULL) {
    hit_test h = intersect(test_ray, ss->s);
    if (!h.miss)
      return 1;
    ss = ss->next;
  }
  return 0;
}

int rgb_nonzero(rgb c)
{
  return (c.r>0 || c.g>0 || c.b>0);
}

rgb lighting(scene s, ray r, hit_test h)
{
  rgb result;
  if (h.miss)
    return s.bg;
  vec hit_position = ray_position(r, h.dist);
  if (shadow(hit_position, s.light, s.spheres)) {
    result = rgb_modulate(h.surf, s.amb);
  }
  else {
    double dot = vec_dot(h.surf_norm, s.light.direction);
    double d = double_max(0, dot);
    rgb diffuse_light = rgb_scale(d, s.light.color);
    rgb lsum = rgb_add(s.amb, diffuse_light);
    result = rgb_modulate(h.surf, lsum);
  }
  /**** === implement specular reflection here === ****/
  if (rgb_nonzero(h.shine)) {
    rgb spec;
    vec N = h.surf_norm;
    vec L = vec_norm(s.light.direction);
    rgb S = h.shine;
    vec R = vec_sub(vec_scale(2 * vec_dot(N, L), N), L);
    vec V = vec_neg(r.direction);
    if (vec_dot(N, L) > 0)
      spec = rgb_scale(pow(double_max(vec_dot(R, V), 0), 6), S);
    else
      spec = rgb_expr(0, 0, 0);
    result = rgb_add(spec, result);
  }
  return result;
}

vec logical_loc(camera c, vec p)
{
  double pixw, pixh;
  double lx, ly;
  if (c.h>c.w)
    pixh = pixw = 2.0 / c.h;
  else
    pixh = pixw = 2.0 / c.w;
  if (p.x>c.w || p.y>c.h) {
    fprintf(stderr, "logical_loc: bad position (%lg, %lg)\n", p.x, p.y);
    exit(1);
  }
  lx = -1.0 + (pixw * p.x) + (pixw / 2.0);
  ly =  1.0 - ((pixh * p.y) + (pixh / 2.0));
  if (c.w>c.h)
    ly -= (c.w-c.h) / 2.0 * pixh;
  else
    lx += (c.h-c.w) / 2.0 * pixw;
  vec result = {lx, ly, 0};
  return result;
}

rgb trace_ray(scene s, ray r)
{
  hit_test closest_hit = {0}, /* {0} to quiet the compiler */
           temp_hit = {0};
  sphere_list *ss = s.spheres;
  closest_hit.miss=1;
  while (ss!=NULL) {
    temp_hit = intersect(r, ss->s);
    if (closest_hit.miss)
      closest_hit = temp_hit;
    else if (!(temp_hit.miss) && !(closest_hit.miss) &&
	     temp_hit.dist < closest_hit.dist)
      closest_hit = temp_hit;
    ss = ss->next;
  }
  return lighting(s, r, closest_hit);
}

/* ALTERED FROM ORIGINAL RENDER TO AUTOMATE FILE CREATION */
/* i hope that's ok */
void render(stage g)
{
  FILE * pFile;
  pFile = fopen ("img.ppm","w");
  if (pFile!=NULL)
  {
    int i, j;
    fprintf(pFile, "P3\n");
    fprintf(pFile, "%d %d\n", g.c.w, g.c.h);
    fprintf(pFile, "255\n");
    for(i=0; i < g.c.h; i++) {
      for(j=0; j < g.c.w; j++) {
        vec p = {j,i,0};
        vec loc = logical_loc(g.c, p);
        vec dir = vec_sub(loc, g.c.loc);
        vec normdir = vec_norm(dir);
        ray r = {g.c.loc, normdir};
        rgb col = trace_ray(g.s ,r);
        rgb_fprint_bytes(pFile, col);
      }
    }
    fclose (pFile);
  } 
  else 
  {
    fprintf(stderr, "frender: failed to create file: \n");
    exit(1);
  }
}

/* fintersect is like intersect, but uses the timestamp */
/* to compute the surface color and specular reflection */
/* color of the intersecting fsphere (if there is one)  */
hit_test fintersect(ray r, fsphere s, timestamp ts)
{
  hit_test result = {0}; /* {0} to quiet the compiler */
  vec sc = s.center;
  double sr = s.radius;
  vec A = vec_sub(r.origin, sc);
  double B = vec_dot(A, r.direction);
  double C = vec_dot(A, A) - (sr * sr);
  double D = (B * B) - C;
  double t = (-B - sqrt(D));
  result.miss = 1;
  if (D > 0 && t > 0) {
    result.miss = 0;
    result.dist = t;
    result.surf = s.compute_surf(s.center, ray_position(r,t), ts);
    result.shine = s.compute_shine(ts);
    result.surf_norm = vec_norm(vec_sub(ray_position(r,t),sc));
  }
  return result;
}

/* fshadow is like shadow, but needs to pass a timestamp */
/* to fintersect                                         */
int fshadow(vec p, light l, fsphere_list *ss, timestamp ts)
{
  vec nudge = vec_scale(0.0001, l.direction);
  vec lifted = vec_add(p, nudge);
  ray test_ray = {lifted, l.direction};
  while (ss!=NULL) {
    hit_test h = fintersect(test_ray, ss->s, ts);
    if (!h.miss)
      return 1;
    ss = ss->next;
  }
  return 0;
}

/* flighting is like lighting, but consumes a frame */
/* rather than a scene                              */
rgb flighting(frame f, ray r, hit_test h)
{
  rgb result;
  if (h.miss)
    return f.bg;
  vec hit_position = ray_position(r, h.dist);
  if (fshadow(hit_position, f.light, f.spheres, f.ts)) {
    result = rgb_modulate(h.surf, f.amb);
  }
  else {
    double dot = vec_dot(h.surf_norm, f.light.direction);
    double d = double_max(0, dot);
    rgb diffuse_light = rgb_scale(d, f.light.color);
    rgb lsum = rgb_add(f.amb, diffuse_light);
    result = rgb_modulate(h.surf, lsum);
  }
  /**** === implement specular reflection here === ****/
  if (rgb_nonzero(h.shine)) {
    rgb spec;
    vec N = h.surf_norm;
    vec L = vec_norm(f.light.direction);
    rgb S = h.shine;
    vec R = vec_sub(vec_scale(2 * vec_dot(N, L), N), L);
    vec V = vec_neg(r.direction);
    if (vec_dot(N, L) > 0)
      spec = rgb_scale(pow(double_max(vec_dot(R, V), 0), 6), S);
    else
      spec = rgb_expr(0, 0, 0);
    result = rgb_add(spec, result);
  }
  return result;
}

/* ftrace is like trace, but for frames rather than scenes */
rgb ftrace(ray r, frame f)
{
  hit_test closest_hit = {0}, /* {0} to quiet the compiler */
           temp_hit = {0};
  fsphere_list *ss = f.spheres;
  closest_hit.miss=1;
  while (ss!=NULL) {
    temp_hit = fintersect(r, ss->s, f.ts);
    if (closest_hit.miss)
      closest_hit = temp_hit;
    else if (!(temp_hit.miss) && !(closest_hit.miss) &&
       temp_hit.dist < closest_hit.dist)
      closest_hit = temp_hit;
    ss = ss->next;
  }
  return flighting(f, r, closest_hit);
}

/* frender consumes a camera and a frame and renders the frame, */
/* writing a ppm file to the given filename                     */
/* - use fopen to open the file, and fclose when you're done    */
void frender(camera c, frame f, char *filename)
{
  FILE * pFile;
  pFile = fopen (filename,"w");
  if (pFile!=NULL)
  {
    int i, j;
    fprintf(pFile, "P3\n");
    fprintf(pFile, "%d %d\n", c.w, c.h);
    fprintf(pFile, "255\n");
    for(i=0; i < c.h; i++) {
      for(j=0; j < c.w; j++) {
        vec p = {j,i,0};
        vec loc = logical_loc(c, p);
        vec dir = vec_sub(loc, c.loc);
        vec normdir = vec_norm(dir);
        ray r = {c.loc, normdir};
        rgb col = ftrace(r, f);
        rgb_fprint_bytes(pFile, col);
      }
    }
    fclose (pFile);
  } 
  else 
  {
    fprintf(stderr, "frender: failed to create file: %s\n", filename);
    exit(1);
  }
}

/* frender_frames renders all frames given an fstage and writes them to files */
/* note: the string name_stem determines the file names */
/* ex: if name_stem is "myframe" and there are 100 frames to render, the filenames */
/*     should be "myframe00.ppm", "myframe01.ppm", ... "myframe99.ppm" */
/* ex: if name_stem is "zz" and there are 100 frames to render, the filenames */
/*     should be "zz00.ppm", "zz01.ppm", ... "zz99.ppm" */
/* note: you *may* include additional leading zeroes if you prefer, just make */
/*       sure the number of digits in each filename is constant, and that     */
/*       files are numbered consecutively */
/*       - this means the following are both OK: */
/*         "zz00.ppm", "zz01.ppm", ... "zz99.ppm" */
/*         "zz0000.ppm", "zz0001.ppm", ... "zz0099.ppm" */
void frender_frames(fstage g, char *name_stem)
{
  int i;
  int width = g.n_frames > 0 ? (int) log10 ((double) g.n_frames) + 1 : 1;
  for (i = 0; i < g.n_frames; i++)
  {
    char fname[128];
    sprintf(fname, "%s%0*d.ppm", name_stem, width, i);
    frender(g.c, g.compute_frame(i), fname);
  }
  return;
}

int main(int argc, char *argv[])
{
  // stage g = get_stage(NULL);
  // render(g);

  fstage g = get_fstage(NULL);
  frender_frames(g, "movie");
  return 0;
}
