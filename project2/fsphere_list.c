#include "raytracer.h"

fsphere_list *fsl_cons(fsphere s, fsphere_list* ss)
{
  fsphere_list *p = malloc(sizeof(fsphere_list));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "fsl_cons: allocation failed.");
    exit(1);
  }

  p->s = s;
  p->next = ss;
  return p;
}
