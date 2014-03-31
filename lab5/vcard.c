#include <stdlib.h>
#include <stdio.h>

#include "addressbook.h"

void vcard_todo(char *s)
{
  fprintf(stderr, "TODO[vcard]: %s\nhalting\n", s);
  exit(1);
}

/* Construct a new vcard */
/* Copy each string with strdup during construction. */
/* (This is a deep-copying constructor.) */
vcard *vcard_new(char *cnet, char *email, char *fname, char *lname, char *tel)
{
  if (cnet == NULL || email == NULL || fname == NULL || lname == NULL || tel == NULL)
  {
    fprintf(stderr, "%s\n", "vcard_new: parameter is NULL");
    exit(1);
  }
  char *cnet_copy = strdup(cnet);
  char *email_copy = strdup(email);
  char *fname_copy = strdup(fname);
  char *lname_copy = strdup(lname);
  char *tel_copy = strdup(tel);
  vcard *p = malloc(sizeof(vcard));
  if (cnet_copy == NULL || email_copy == NULL || fname_copy == NULL || lname_copy == NULL || tel_copy == NULL || p == NULL)
  {
    fprintf(stderr, "%s\n", "vcard_new: allocation failed.");
    exit(1);
  }
  p->cnet = cnet_copy;
  p->email = email_copy;
  p->fname = fname_copy;
  p->lname = lname_copy;
  p->tel = tel_copy;
  return p;
}

/* Display vcard to stdout. */
/* The display of a vcard need not match any exact specification, */
/* but it must include all five of the vcard's component strings. */
void vcard_show(vcard *c)
{
  if (c == NULL)
  {
    fprintf(stderr, "%s\n", "vcard_show: parameter is NULL");
    exit(1);
  }
  printf("%s\n", "-----------------------");
  printf("CNET: %s\n" , c->cnet);
  printf("EMAIL: %s\n", c->email);
  printf("FIRST NAME: %s\n", c->fname);
  printf("LAST NAME: %s\n", c->lname);
  printf("TELE: %s\n",  c->tel);
  printf("%s\n", "-----------------------");
  return;
}

/* Free the vcard and all strings in it. */
void vcard_free(vcard *c)
{
  free(c->cnet);
  free(c->email);
  free(c->fname);
  free(c->lname);
  free(c->tel);
  free(c);
  return;
}


// int main()
// {
//   vcard *v = vcard_new("victorcheung", "victorcheung@uchicago.edu", "Victor", "Cheung", "7738922471");
//   vcard_show(v);
//   vcard_free(v);

// }
