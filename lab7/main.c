#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <ctype.h>

#include "sll.h"
#include "htbl.h"

#define DEFAULT_SIZE 10  /* default hash table size */
#define MAX_LINE_LEN 256 /* maximum length for lines read from stdin */

/* allocate a string on the heap and fill it with '\0' */
char *alloc_str(int sz)
{
  int i;
  char *s = malloc(sz);
  if (s==NULL) {
    fprintf(stderr,"alloc_str: malloc failed\n");
    exit(1);
  }
  for (i=0; i<sz; i++)
    s[i] = '\0';
  return s;
}

/* trim_newline replaces the newline at the end of the string (if there
 * is one) with '\0', and then calls strdup on the result,
 * returning a pointer to the duplicated string.
 */
char *trim_newline(char *s)
{
  char *t;
  int n = strlen(s);
  int must_change = (s[n-1]=='\n');
  if (must_change)
    s[n-1] = '\0';
  t = strdup(s);
  if (must_change)
    s[n-1] = '\n'; /* tidy up */
  return t;
}

/* display usage message */
void usage(char *exec_name)
{
  fprintf(stderr,"Usage: %s [OPTIONS]\n", exec_name);
  fprintf(stderr,"Options:\n");
  fprintf(stderr,"  -s <num>\tuse <num> (positive int) table size\n");
}

/* main:
 * read an optional size argument for hash table,
 * read in strings from standard input,
 * build hash table,
 * display hash table and a few statistics */
int main(int argc, char *argv[])
{
  htbl *t;
  int sz = DEFAULT_SIZE;
  char c;
  /* note: read about "getopt" to learn about command-line arg processing */
  while ((c=getopt(argc,argv,"s:"))!=-1) {
    switch (c) {
    case 's':
      sz = atoi(optarg);
      if (sz<1) {
	fprintf(stderr,"%s error: nonpositive table size %d\n",*argv,sz);
	exit(1);
      }
      break;
    case '?':
      usage(*argv);
      exit(1);
    }
  }
  /* build a new empty hash table */
  t = htbl_init(sz);
  /* read a line at a time from stdin, add non-empty strings to the table */
  while (!feof(stdin)) {
    char *s = alloc_str(MAX_LINE_LEN);
    char *l;
    fgets(s,MAX_LINE_LEN,stdin);
    l = trim_newline(s);
    free(s);
    if (strlen(l)>0)
      htbl_add(l,t);
    free(l);
  }
  htbl_show(t);
  printf("\nThe hash table has %i buckets with %i entries (load factor %lg).\n",
	 t->n_buckets,
	 htbl_n_entries(t),
	 htbl_load_factor(t));
  /* test hash table membership */
  /* "xyz" is not in the cnet file; "al578" is */
  printf("\ntesting htbl_member:\n");
  printf("membership of cnet \"xyz\"  : %i\n", htbl_member("xyz",t));
  printf("membership of cnet \"al578\": %i\n", htbl_member("al578",t));
  htbl_free(t);
  return 0;
}
