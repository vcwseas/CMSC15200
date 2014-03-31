// Victor Cheung, VCheung
// CMSC 15200, win14
// Project1, raytracer

#include "raytracer.h"


vec *logical_loc_aux_y_greater(camera *c, vec *pos)
{
  double sidelength = 2.0 / c->h;
  double base_center_y = 1 - sidelength / 2.0;
  double center_y = base_center_y - pos->y * sidelength;

  double short_side_length = sidelength * c->w;
  double topleft_short_side = short_side_length / 2.0;
  double base_center_x = (- topleft_short_side) + sidelength / 2.0;
  double center_x = base_center_x + pos->x * sidelength;
  return vec_new(center_x, center_y, 0);
}

vec *logical_loc_aux_x_greater(camera *c, vec *pos)
{
  double sidelength = 2.0 / c->w;
  double base_center_x = -1 + sidelength / 2.0;
  double center_x = base_center_x + pos->x * sidelength;

  double short_side_length = sidelength * c->h;
  double topleft_short_side = short_side_length / 2.0;
  double base_center_y = topleft_short_side - sidelength / 2.0;
  double center_y = base_center_y - pos->y * sidelength;
  return vec_new(center_x, center_y, 0);
}

/* gives the logical location given a camera
anad a position in the physical plane */
vec *logical_loc(camera *c, vec *pos)
{
  if (c->h > c->w)
    return logical_loc_aux_y_greater(c, pos);
  else
    return logical_loc_aux_x_greater(c, pos);
}

/* only job is to clean up intersect */
void intersect_clean(vec *a, vec *b, vec *c, vec *d)
{
  vec_free(a);
  vec_free(b);
  vec_free(c);
  vec_free(d);
}

/* tests whether or not a ray intersects a sphere */
hit_test *intersect(ray *r, sphere *s)
{
  if (r == NULL || s == NULL)
  {
    fprintf(stderr, "%s\n", "intersect: parameter is NULL");
    exit(1);
  }

  vec *unit_direction = vec_norm(r->direction);
  vec *A = vec_sub(r->origin, s->center);
  double B = vec_dot(A, unit_direction);
  double C = vec_dot(A, A) - (s->radius * s->radius);
  double D = (B * B) - C;

  double t = (-B - sqrt(D));
  if (D > 0 && t > 0)
  {
    vec *pos = ray_position(r, t);
    vec *sub = vec_sub(pos, s->center);
    vec *surf_norm = vec_norm(sub);

    // clean up used vectors
    intersect_clean(pos, sub, unit_direction, A);

    return hit_test_new(t, s->color, surf_norm);
  }

  vec_free(A);
  vec_free(unit_direction);
  return NULL;
}

/* all I do is clean up after Shadow. Thanks Shadow. */
void shadow_clean(ray *d, hit_test *e)
{
  ray_free(d);
  hit_test_free(e);
}

/* computes whether a location is in shadow */
int shadow(vec *v, light *l, sphere_list *ss)
{
  if (v == NULL || l == NULL || ss == NULL)
  {
    fprintf(stderr, "%s\n", "shadow: parameter is NULL");
    exit(1);
  }

  vec *light_direction = vec_norm(l->direction);
  vec *nudge = vec_scale(0.00001, light_direction);
  vec *lifted = vec_add(nudge, v);
  vec_free(nudge);
  ray *shadow_ray = ray_new(lifted, light_direction);
  hit_test *tmp;

  while (ss != NULL)
  {
    if ((tmp = intersect(shadow_ray, ss->s)) != NULL)
    {
      shadow_clean(shadow_ray, tmp);
      return 1;
    }
    else if (tmp != NULL)
    {
      hit_test_free(tmp);
    }
    ss = ss->next;
  }
  if (shadow_ray != NULL)
    ray_free(shadow_ray);

  return 0;
}

double max(double a, double b)
{
  return a > b ? a : b;
}


void lighting_clean(vec *a, rgb *b, rgb *c, hit_test *e)
{
  vec_free(a);
  rgb_free(b);
  rgb_free(c);
  hit_test_free(e);
}

/* Compute the color for the hit test.
 * If hit-test is a miss (NULL), the color is the scene's background color.
 * Otherwise, it is determined by diffuse lighting (see below) at hit point. */

rgb *lighting(scene *s, ray *r, hit_test *h)
{
  if (s == NULL || r == NULL)
  {
    fprintf(stderr, "%s\n", "lighting: parameter is NULL ");
    exit(1);
  }

  if (h == NULL)
  {
    rgb *dup = rgb_dup(s->bg);
    return dup;
  }
  else
  {
    vec *ray_pos = ray_position(r, h->dist);
    if (shadow(ray_pos, s->light, s->spheres) == 0)
    {
      double maxVal = max(0, vec_dot(h->surf_norm, s->light->direction));
      rgb *diffuse = rgb_scale(maxVal, s->light->color);

      rgb *sum = rgb_add(diffuse, s->amb);
      rgb *result = rgb_modulate(h->surf_color, sum);
      lighting_clean(ray_pos, diffuse, sum, h);
      return result;
    }
    else
    {
      rgb *res = rgb_modulate(s->amb, h->surf_color);
      vec_free(ray_pos);
      hit_test_free(h);
      return res;
    }
  }
}

/*  traces a ray from the camera into a scene
    testing for intersections with any spheres
    and finding either the closest intersection
    or a miss, then using lighting to compute
    the color.
*/
rgb *trace_ray(scene *s, ray *r)
{
  if (s == NULL || r == NULL)
  {
    fprintf(stderr, "%s\n", "trace_ray: parameter is NULL");
    exit(1);
  }

  hit_test *min = NULL;
  hit_test *tmp;
  sphere_list *ss = s->spheres;

  while (ss != NULL)
  {
    if (min == NULL)
    {
      if ((tmp = intersect(r, ss->s)) != NULL)
      {
        min = tmp;
      }
    }
    else if ((tmp = intersect(r, ss->s)) != NULL && tmp->dist < min->dist)
    {
      hit_test_free(min);
      min = tmp;
    }
    ss = ss->next;
  }

  return lighting(s, r, min);
}

/* renders an image */
void render(stage *g)
{
  if (g == NULL)
  {
    fprintf(stderr, "%s\n", "render; parameter is NULL");
    exit(1);
  }

  int width = g->c->w;
  int height = g->c->h;
  ray *camera_ray = ray_new(vec_dup(g->c->loc), NULL);
  vec *phys;
  vec *logic;
  vec *logical_direction;
  vec *cdirection;
  rgb *res;


  printf("P3\n%u %u\n255\n", width, height);

  int i, j;
  for (i = 0; i < height; i++)
  {
    for (j = 0; j < width; j++)
    {
      phys = vec_new(j, i, 0);
      logic = logical_loc(g->c, phys);
      logical_direction = vec_sub(logic, g->c->loc);
      cdirection = vec_norm(logical_direction);
      camera_ray->direction = cdirection;
      res = trace_ray(g->s, camera_ray);

      rgb_print_bytes(res);

      rgb_free(res);
      vec_free(phys);
      vec_free(logic);
      vec_free(logical_direction);
      vec_free(cdirection);
    }
  }
  vec_free(camera_ray->origin);
  free(camera_ray);
}

int main(int argc, char *argv[])
{
  stage *st = get_stage("2");
  render(st);
  stage_free(st);
  return 1;
}
