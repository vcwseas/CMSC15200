// Victor Cheung, VCheung
// CMSC15200, Win14
// Lab4, stage

#include "raytracer.h"

/* constructor for a stage */
stage *stage_new(camera *c, scene *s)
{
  if (c == NULL || s == NULL)
  {
    fprintf(stderr, "%s\n", "stage_new: parameter is NULL");
    exit(1);
  }

  stage *p = malloc(sizeof(stage));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "stage_new: allocation failed.");
    exit(1);
  }
  p->c = c;
  p->s = s;
  return p;
}

/* allocates a new stage on the heap */
stage *stage_dup(stage *st)
{
  if (st == NULL)
  {
    fprintf(stderr, "%s\n", "stage_dup: parameter is NULL");
    exit(1);
  }
  return stage_new(camera_dup(st->c), scene_dup(st->s));
}

/* prints a stage in string format */
void stage_print(stage *st)
{
  if (st == NULL)
  {
    fprintf(stderr, "%s\n", "stage_print: parameter is NULL");
    exit(1);
  }
  printf("STAGE - camera:");
  camera_print(st->c);
  printf(", scene: ");
  scene_print(st->s);
  printf("- END STAGE STRUCT\n");
  return;
}

/* destructor for a stage */
void stage_free(stage *st)
{
  camera_free(st->c);
  scene_free(st->s);
  free(st);
  return;
}

/* returns a predetermined testing stage */
stage *get_stage(char *future_expansion)
{
  // 2012 IMAGE 7
  switch(atoi(future_expansion))
  {
    case 1:
    {
      camera *c1 = camera_new(vec_new(0.0, 0.0, -5.0), 200, 200);
      sphere *s1 = sphere_new(vec_new(1, -1, 8.0), 2.0, rgb_new(1, 1, 0.941));
      sphere *s2 = sphere_new(vec_new(-1.0/3.0, 1, 5.0), 3.0/4.0, rgb_new(1, 1, 0.941));
      sphere_list *ss = sl_cons(s1, sl_singleton(s2));

      vec *tmp = vec_new(-1.0, 1.0, -1.0);

      light *l1 = light_new(vec_norm(tmp), rgb_new(1.0, 1.0, 1.0));
      vec_free(tmp);

      scene *sc1 = scene_new(rgb_new(0.0, 0.0, 0.0), ss, l1, rgb_new(0.2, 0.2, 0.2));
      stage *st1 = stage_new(c1, sc1);
      return st1;
    }

  // 2012 IMAGE 10
  case 2:
    {
      camera *c1 = camera_new(vec_new(0.0, 0.0, -8.0), 400, 400);
      sphere *s1 = sphere_new(vec_new(1, -1, 8.0), 2.0, rgb_new(1, 1, 0.941));
      sphere *s2 = sphere_new(vec_new(-1.0/3.0, 1, 5.0), 3.0/4.0, rgb_new(1, 1, 0.941));
      sphere_list *ss = sl_cons(s1, sl_singleton(s2));

      vec *tmp = vec_new(-0.5, 1, -1.0);

      light *l1 = light_new(vec_norm(tmp), rgb_new(1.0, 0, 0));
      vec_free(tmp);

      scene *sc1 = scene_new(rgb_new(0.0, 0.0, 0.0), ss, l1, rgb_new(0.2, 0.2, 0.2));
      stage *st1 = stage_new(c1, sc1);
      return st1;
    }


  // 2012 IMAGE 5
    case 3:
    {
      camera *c1 = camera_new(vec_new(0.0, 0.0, -5.0), 200, 200);
      sphere *s1 = sphere_new(vec_new(1.5, 0, 8.0), 1.0, rgb_new(0.1176, 0.5647, 1.0));
      sphere *s2 = sphere_new(vec_new(-1.5, 0, 8.0), 1, rgb_new(0.1176, 0.5647, 1.0));
      sphere *s3 = sphere_new(vec_new(0, 0, 20), 1, rgb_new(0.7529, 0.7529, 0.7529));
      sphere_list *ss = sl_cons(s3, sl_cons(s1, sl_singleton(s2)));

      vec *tmp = vec_new(-1.0, 1.0, -1.0);

      light *l1 = light_new(vec_norm(tmp), rgb_new(1.0, 1.0, 1.0));
      vec_free(tmp);

      scene *sc1 = scene_new(rgb_new(0.0, 0.0, 0.0), ss, l1, rgb_new(0.2, 0.2, 0.2));
      stage *st1 = stage_new(c1, sc1);
      return st1;
    }

    case 4:
    {
      camera *c1 = camera_new(vec_new(0.0, 0, -5), 180, 180);
      sphere *s1 = sphere_new(vec_new(0, 0, 3.0), 1.0, rgb_new(0.8, 0.8, 0.8));
      sphere_list *ss = sl_singleton(s1);
      vec *tmp = vec_new(-1.0, 1.0, -1.0);

      light *l1 = light_new(vec_norm(tmp), rgb_new(1.0, 1.0, 1.0));
      vec_free(tmp);
      scene *sc1 = scene_new(rgb_new(0.3, 0.6, 1.0), ss, l1, rgb_new(0.2, 0.2, 0.2));
      stage *st1 = stage_new(c1, sc1);
      return st1;
    }

    case 5:
    {
      camera *c1 = camera_new(vec_new(0.0, 0, -5), 360, 540);
      sphere *s1 = sphere_new(vec_new(0, 0, 3.0), 1.0, rgb_new(0.8, 0.8, 0.8));
      sphere_list *ss = sl_singleton(s1);
      vec *tmp = vec_new(-1.0, 1.0, -1.0);

      light *l1 = light_new(vec_norm(tmp), rgb_new(1.0, 1.0, 1.0));
      vec_free(tmp);
      scene *sc1 = scene_new(rgb_new(0.3, 0.6, 1.0), ss, l1, rgb_new(0.2, 0.2, 0.2));
      stage *st1 = stage_new(c1, sc1);
      return st1;
    }

  }

}
