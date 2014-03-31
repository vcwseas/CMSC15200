#include <stdlib.h>
#include <stdio.h>

#include "addressbook.h"

/* Create a bst consisting of one leaf node. */
bst *bst_singleton(vcard *c)
{
  if (c == NULL)
  {
    fprintf(stderr, "%s\n", "bst_singleton: parameter is NULL");
    exit(1);
  }

  bst *p = malloc(sizeof(bst));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "bst_singleton: allocation failed.");
    exit(1);
  }

  p->c = c;
  p->lsub = NULL;
  p->rsub = NULL;
  return p;
}


/* Insert a vcard into a BST and return a pointer to the modified tree. */
/* Use cnet alphabetical order. */
/* Does not copy the vcard (this is shallow-copy insert). */
/* if cnet id repeats, then the new card replaces the old one */
bst *bst_insert(bst *t, vcard *c)
{
  if (t == NULL)
  {
    return bst_singleton(c);
  }
  //strcmp
  //  - returns 0 if they're equal
  //  - returns >0 if c->net > t->c->cnet
  //  - returns <0 if t->c->cnet > c->net
  int cv = strcmp(c->cnet, t->c->cnet);

  if (cv < 0)
  {
    t->lsub = bst_insert(t->lsub, c);
    return t;
  }
  else if (cv > 0)
  {
    t->rsub = bst_insert(t->rsub, c);
    return t;
  }
  else if (cv == 0)
  {
    free(t->c);
    t->c = c;
    return t;
  }

  fprintf(stderr, "%s\n", "bst_insert: failed to insert vcard.");
  exit(1);
}

/* Compute the total number of vcards in the tree. */
unsigned int bst_num_entries(bst *t)
{
  if (t == NULL)
  {
    return 0;
  }
  else return 1 + bst_num_entries(t->lsub) + bst_num_entries(t->rsub);
}

/* The empty bst has height 0. */
/* A singleton tree has height 1, etc. */
unsigned int bst_height(bst *t)
{
  if (t == NULL)
    return 0;
  else
  {
    unsigned int left = bst_height(t->lsub);
    unsigned int right = bst_height(t->rsub);
    return left > right? left + 1: right + 1;
  }
}

/* Return NULL if nothing is found. */
/* n_comparisons is an out parameter to count the number of */
/* comparisons made during the search. */
vcard *bst_search(bst *t, char *cnet, int *n_comparisons)
{
  if (t == NULL)
  {
    return NULL;
  }
  else
  {
    int cv = strcmp(cnet, t->c->cnet);
    *n_comparisons = *n_comparisons + 1;
    return cv == 0 ? t->c : (cv < 0 ? bst_search(t->lsub, cnet, n_comparisons) : bst_search(t->rsub, cnet, n_comparisons));
  }
}

/* Free the bst and all vcards as well. */
void bst_free(bst *t)
{
  if (t == NULL)
  {
    return;
  }
  free(t->c);
  bst_free(t->lsub);
  bst_free(t->rsub);
  free(t);
}

