#ifndef _ADDRESSBOOK_H_
#define _ADDRESSBOOK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vcard{
  char *cnet;
  char *email;
  char *fname;
  char *lname;
  char *tel;
} vcard;
typedef struct bst bst;
struct bst {
  vcard *c;
  bst *lsub;
  bst *rsub;
};

/* ============================ */
/* ===== vcard operations ===== */
/* ============================ */

/* Construct a new vcard */
/* Copy each string with strdup during construction. */
/* (This is a deep-copying constructor.) */
vcard *vcard_new(char *cnet, char *email, char *fname, char *lname, char *tel);

/* Display vcard to stdout. */
/* The display of a vcard need not match any exact specification, */
/* but it must include all five of the vcard's component strings. */
void vcard_show(vcard *c);

/* Free the vcard and all strings in it. */
void vcard_free(vcard *c);

/* ============================ */
/* =====  bst operations  ===== */
/* ============================ */

/* Create a bst consisting of one leaf node. */
bst *bst_singleton(vcard *c);

/* Insert a vcard into a BST and return a pointer to the modified tree. */
/* Use cnet alphabetical order. */
/* Do not copy the vcard (this is shallow-copy insert). */
bst *bst_insert(bst *t, vcard *c);

/* Compute the total number of vcards in the tree. */
unsigned int bst_num_entries(bst *t);

/* The empty bst has height 0. */
/* A singleton tree has height 1, etc. */
unsigned int bst_height(bst *t);

/* Return NULL is nothing is found. */
/* n_comparisons is an out parameter to count the number of */
/* comparisons made during the search. */
vcard *bst_search(bst *t, char *cnet, int *n_comparisons);

/* Free the bst and all vcards as well. */
void bst_free(bst *t);


#endif /* _ADDRESSBOOK_H_ */
