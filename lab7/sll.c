// Victor Cheung, VCheung
// CS152, win14
// lab7

#include "sll.h"


/* By convention, the empty list is NULL. */

/* sll_cons : (char*, sll*) -> sll* */
/* build new list with given string at the head */
/* note: copy the given string to the list (deep copy strategy) */
sll *sll_cons(char *s, sll *ss)
{
  sll *p = malloc(sizeof(sll));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "sll_cons: allocaiton faled.");
    exit(1);
  }

  p->s = strdup(s);
  if (p->s == NULL)
  {
    fprintf(stderr, "%s\n", "sll_cons: strdup failed.");
    exit(1);
  }
  p->next = ss;
  return p;
}

/* sll_length : sll* -> int */
/* return the number of strings in the given list */
unsigned int sll_length(sll *ss)
{
  unsigned int count = 0;
  while (ss != NULL)
  {
    count++;
    ss = ss->next;
  }
  return count;
}

/* sll_member : (char*, sll*) -> int */
/* test membership of given string in given list */
/* use strcmp to compare strings */
int sll_member(char *s, sll *ss)
{
  while (ss != NULL)
  {
    if (strcmp(s, ss->s) == 0)
    {
      return 1;
    }
    ss = ss->next;
  }
  return 0;
}

/* sll_show : sll* -> <void> */
/* print a representation of the linked list to stdout */
void sll_show(sll *ss)
{
  while (ss != NULL)
  {
    printf("%s\n", ss->s);
    ss = ss->next;
  }
  return;
}

/* sll_free : sll* -> <void> */
void sll_free(sll *ss)
{
  if (ss == NULL)
    return;
  else
  {
     free(ss->s);
     sll *tmp = ss->next;
     free(ss);
     sll_free(tmp);
  }
}
