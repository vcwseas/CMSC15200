// Victor Cheung, VCheung
// CS152, win14
// Lab7

#include "htbl.h"

/* hash : char -> unsigned int */
/* compute hash code for given string */
/* see web page for algorithm */
unsigned long int hash(char *s)
{
  unsigned long int res = 17;
  while (*s != '\0' )
  {
    res = res * 37 + *s;
    s++;
  }
  return res;
}

/* htbl_init : int -> htbl* */
/* allocate space for a new hash table of given size */
/* all buckets must initially contain the empty list */
htbl *htbl_init(int sz)
{
  htbl *p = malloc(sizeof(htbl));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "htbl_init: allocaiton failed.");
    exit(1);
  }

  p->n_buckets = sz;

  sll **buckets = malloc(sizeof(sll *) * sz);

  if (buckets == NULL)
  {
    fprintf(stderr, "%s\n", "htbl_init: allocation failed.");
    exit(1);
  }

  int i;
  for (i = 0; i < sz; i++)
  {
    buckets[i] = NULL;
  }

  p->buckets = buckets;
  return p;
}

/* htbl_n_entries : htbl* -> unsigned int */
/* return the total number of entries in all buckets */
unsigned int htbl_n_entries(htbl *t)
{
  if (t == NULL)
  {
    fprintf(stderr, "%s\n", "htbl_n_entires: parameter is NULL.");
    exit(1);
  }
  unsigned int count = 0;
  int i;
  for (i = 0; i < t->n_buckets; i++)
  {
    count += sll_length(t->buckets[i]);
  }
  return count;
}

/* htbl_load_factor : htbl* -> float */
/* The load factor is the mean number of elements per bucket. */
double htbl_load_factor(htbl *t)
{
  unsigned int total = htbl_n_entries(t);
  return ((double) total) / ((double) t->n_buckets);
}

/* htbl_add : (char*, htbl*) -> int */
/* add string s to hash table t */
/* return the number of strings in s's bucket _after_ inserting it */
unsigned int htbl_add(char *s, htbl *t)
{
  unsigned long int code = hash(s);
  unsigned int index = code % t->n_buckets;
  if (!sll_member(s, t->buckets[index]))
    t->buckets[index] = sll_cons(s, t->buckets[index]);
  return sll_length(t->buckets[index]);
}

/* htbl_member : (char*, htbl*) -> int */
/* test membership of given string in given table */
/* the integer returned is a quasi-boolean */
int htbl_member(char *s, htbl *t)
{
  if (t == NULL)
  {
    fprintf(stderr, "%s\n", "htbl_member: paramter is NULL.");
    exit(1);
  }
  unsigned long int code = hash(s);
  unsigned int index = code % t->n_buckets;

  return sll_member(s, t->buckets[index]);
}

/* htbl_show : htbl* -> <void> */
/* print a represntation of the hash table to stdout */
void htbl_show(htbl *t)
{
  if (t == NULL)
  {
    fprintf(stderr, "%s\n", "htbl_show: paramter is NULL.");
    exit(1);
  }

  int i;
  for (i = 0; i< t->n_buckets; i++)
  {
    printf("bucket at index %d:\n", i);
    sll_show(t->buckets[i]);
    printf("\n");
  }
  return;
}

/* htbl_free : htbl* -> <void> */
void htbl_free(htbl *t)
{
  int i;
  for (i = 0; i< t->n_buckets; i++)
  {
    sll_free(t->buckets[i]);
  }
  free(t->buckets);
  free(t);
  return;
}
