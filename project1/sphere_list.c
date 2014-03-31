// Victor Cheung, VCheung
// CMSC 15200, Win14
// Project 1, sphere_list

#include "raytracer.h"

/* conses a sphere onto the head of a sphere_list */
sphere_list *sl_cons(sphere *s, sphere_list *ss)
{
  if (s == NULL)
  {
    fprintf(stderr, "%s\n", "sphere_list: sphere parameter is NULL");
    exit(1);
  }
  sphere_list *sl = malloc(sizeof(sphere_list));
  if (sl == NULL)
  {
    fprintf(stderr, "%s\n", "sphere_list: allocation failed.");
    exit(1);
  }
  sl->s = s;
  sl->next = ss;
  return sl;
}

/* duplicates a sphere list */
sphere_list *sl_dup(sphere_list *sl)
{
  if (sl == NULL)
  {
    fprintf(stderr, "%s\n", "sl_dup: parameter is NULL");
    exit(1);
  }
  sphere_list *p = NULL;
  while (sl != NULL)
  {
    p = sl_cons(sphere_dup(sl->s), p);
    sl = sl->next;
  }
  return p;
}

/* constructor for a sphere_list */
sphere_list *sl_singleton(sphere *s)
{
  if (s == NULL)
  {
    fprintf(stderr, "%s\n", "sl_singleton: sphere parameter is NULL");
    exit(1);
  }
  return sl_cons(s, NULL);
}

/* prints a sphere list */
void sl_print(sphere_list *ss)
{
  if (ss == NULL)
  {
    return;
  }
  printf("%s", "SPHERE LIST - \n");
  while (ss != NULL)
  {
    sphere_print(ss->s);
    ss = ss->next;
  }
  printf("%s\n", "- END SPHERE LIST \n");
  return;
}

/* destructor for a sphere list node
   WARNING: destroys just one node and
   sphere; leaves behind previous nodes
   and nodes after */
void sl_free(sphere_list *ss)
{
  sphere_list *tmp;
  while (ss != NULL)
  {
    sphere_free(ss->s);
    tmp = ss->next;
    free(ss);
    ss = tmp;
  }
  return;
}





