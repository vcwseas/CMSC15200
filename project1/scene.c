// Victor Cheung, VCheung
// CMSC 15200, Win 2014
// Lab 4, scene

#include "raytracer.h"

/* constructor for a scene */
scene *scene_new(rgb *bg, sphere_list *ss, light *light, rgb *amb)
{
  if (bg == NULL || ss == NULL || light == NULL || amb == NULL)
  {
    fprintf(stderr, "%s\n", "scene_new: parameter is NULL.");
    exit(1);
  }
  scene *sc = malloc(sizeof(scene));
  if (sc == NULL)
  {
    fprintf(stderr, "%s\n", "scene_new: allocation failure");
    exit(1);
  }
  sc->bg = bg;
  sc->spheres = ss;
  sc->light = light;
  sc->amb = amb;
  return sc;
}

scene *scene_dup(scene *s)
{
  if (s == NULL)
  {
    fprintf(stderr, "%s\n", "scene_dup: parameter is NULL.");
    exit(1);
  }
  return scene_new(rgb_dup(s->bg), sl_dup(s->spheres), light_dup(s->light), rgb_dup(s->amb));
}


/* prints a scene in string format */
void scene_print(scene *s)
{
  if (s == NULL)
  {
    fprintf(stderr, "%s\n", "scene_print: parameter is NULL.");
    exit(1);
  }
  printf("SCENE - background color: %s, sphere list: ", rgb_tos(s->bg));
  sl_print(s->spheres);
  printf(", light: ");
  light_print(s->light);
  printf(", amb: %s - END SCENE STRUCT\n", rgb_tos(s->amb));
  return;
}

/* scene destructor */
void scene_free(scene *s)
{
  rgb_free(s->bg);
  sl_free(s->spheres);
  light_free(s->light);
  rgb_free(s->amb);
  free(s);
}





