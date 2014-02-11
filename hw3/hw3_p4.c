// Victor Chueng, vcheung
// CS152, Win14
// Homework 3, Problem 4
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// a point is a coordinate in Euclidean space
struct point
{
  double x;
  double y;
};

typedef struct point point;

//path contains an array of pointers to points
struct path
{
  point **points;
  unsigned int len;
};
typedef struct path path;

//constructor for a dynamically allocated point
//returns a pointer to a point
point *point_new(double x, double y)
{
  point *p = malloc(sizeof(point));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "point_new: NULL POINTER ERROR");
    exit(1);
  }
  p->x = x;
  p->y = y;
  return p;
}

//destructor for pointers
void point_free(point *p)
{
  free(p);
}

//displays pointers in the format (x, y)
void point_show(point *p)
{
  printf("(%.2lf, %.2lf)", p->x, p->y);
}

//constructor for new dynamically allocated paths
//returns a pointer to a path
path *path_new(point **points, unsigned int len)
{
  path *p = malloc(sizeof(path));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "path_new: NULL POINTER ERROR");
    exit(1);
  }
  p->points = points;
  p->len = len;
  return p;
}

//destructors for a path
void path_free(path *p)
{
  unsigned int i, len = p->len;
  for (i = 0; i < len; i++)
  {
    point_free(p->points[i]);
  }
  free(p);
}

//displays a path in the format (x1, y1) (x2, y2) (x3, y3)...
void path_show(path *p)
{
  unsigned int i, len = p->len;
  for (i = 0; i < len; i++)
  {
    point_show(p->points[i]);
    if (i < len - 1)
      printf(" ");
  }
  printf("\n");
}

//calculates the euclidean distance between points on a plane
double distance(double x1, double y1, double x2, double y2)
{
  return sqrt( pow(fabs(x1 - x2), 2) + pow(fabs(y1 - y2), 2));
}
//calculates the length of a path
double path_length(path *p)
{
  double sum = 0;
  unsigned int i, len = p->len;
  point **points = p->points;
  for (i = 0; i < len - 1; i++)
  {
    sum += distance(points[i]->x, points[i]->y,
     points[i+1]->x, points[i+1]->y);
  }
  return sum;
}

//appends a point onto a path
void path_append(path *p, point *q)
{
  unsigned int len = p->len = p->len + 1;
  unsigned int i;
  point **points = p->points;
  point **ptonewarr = malloc(len * sizeof(point *));
  for (i = 0; i < len - 1; i++)
  {
    ptonewarr[i] = points[i];
  }
  ptonewarr[i] = q;
  p->points = ptonewarr;
  free(points);
}

int main (int argc, char **argv)
{
  point **ptoarr = malloc(4 * sizeof(point *));
  *ptoarr = point_new(0.0, 0.0);
  *(ptoarr + 1) = point_new(1.0, 0.0);
  *(ptoarr + 2) = point_new(0.0, 0.0);
  ptoarr[3] = point_new(1.0, 0.0);
  path *p = path_new(ptoarr, 4);
  path_show(p);
  printf("The distance is %lf\n", path_length(p));
  path_append(p, point_new(2.0, 2.0));
  path_show(p);
  return 0;
}
