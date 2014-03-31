// Victor Cheung, VCheung
// CMSC15200, Win14
// Lab4, camera

#include "raytracer.h"

/* constructor for a camera struct */
camera *camera_new(vec *loc, unsigned int h, unsigned int w)
{
  if (loc == NULL)
  {
    fprintf(stderr, "%s\n", "camera_new: parameter is NULL");
    exit(1);
  }
  camera *c = malloc(sizeof(camera));
  if (c == NULL)
  {
    fprintf(stderr, "%s\n", "camera_new: allocation failure.");
    exit(1);
  }
  c->loc = loc;
  c->h = h;
  c->w = w;
  return c;
}

/* allocates a new camera on the heap */
camera *camera_dup(camera *c)
{
  if (c == NULL)
  {
    fprintf(stderr, "%s\n", "camera_dup: parameter is NULL");
    exit(1);
  }
  camera *cdup = malloc(sizeof(camera));
  if (cdup == NULL)
  {
    fprintf(stderr, "%s\n", "camera_dup: allocation failed.");
    exit(1);
  }
  cdup->loc = vec_dup(c->loc);
  cdup->h = c->h;
  cdup->w = c->w;
  return cdup;
}

/* outputs a camera in string format */
void camera_print(camera *c)
{
  if (c == NULL)
  {
    fprintf(stderr, "%s\n", "camera_print: parameter is NULL.");
    exit(1);
  }
  printf("CAMERA - loc: %s, h: %u, w: %u - END CAMERA STRUCT\n", vec_tos(c->loc), c->h, c->w);
  return;
}

/*destructor for camera */
void camera_free(camera *c)
{
  vec_free(c->loc);
  free(c);
  return;
}

