// Victor Cheung, VCheung
// CMSC15200, Win14
// HW4, bexp

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct booltree_and bexp_and;
typedef struct booltree_or bexp_or;
typedef struct booltree_not bexp_not;

typedef struct tagged_booltree bexp;

enum bool { BFALSE, BTRUE };
typedef enum bool bool;

struct booltree_and {
  bexp *e1;
  bexp *e2;
};

struct booltree_or {
  bexp *e1;
  bexp *e2;
};

struct booltree_not {
  bexp *e1;
};

union b_union {
  bool bconst;
  bexp_and *and;
  bexp_or  *or;
  bexp_not *not;
};

enum btag { BCONST, AND, OR, NOT };

struct tagged_booltree {
  enum btag tag;
  union b_union e;
};

/* family of constructors */
bexp *bexp_const_new(bool b)
{
  bexp *p = malloc(sizeof(bexp));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_const_new: allocation failure.");
    exit(1);
  }
  p->tag = BCONST;
  p->e.bconst = b;
  return p;
}

bexp *bexp_and_new(bexp *e1, bexp *e2)
{
  if (e1 == NULL || e2 == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_and_new: parameter is NULL.");
    exit(1);
  }
  bexp *p = malloc(sizeof(bexp));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_and_new: allocation failure.");
    exit(1);
  }
  bexp_and *b = malloc(sizeof(bexp_and));
  if (b == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_and_new: allocation failure.");
    exit(1);
  }
  b->e1 = e1;
  b->e2 = e2;
  p->tag = AND;
  p->e.and = b;
  return p;
}


bexp *bexp_or_new(bexp *e1, bexp *e2)
{
  if (e1 == NULL || e2 == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_or_new: parameter is NULL.");
    exit(1);
  }
  bexp *p = malloc(sizeof(bexp));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_or_new: allocation failure.");
    exit(1);
  }
  bexp_or *b = malloc(sizeof(bexp_or));
  if (b == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_or_new: allocation failure.");
    exit(1);
  }
  b->e1 = e1;
  b->e2 = e2;
  p->tag = OR;
  p->e.or = b;
  return p;
}

bexp *bexp_not_new(bexp *e1)
{
  if (e1 == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_not_new: parameter is NULL.");
    exit(1);
  }
  bexp *p = malloc(sizeof(bexp));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_not_new: allocation failure.");
    exit(1);
  }
  bexp_not *b = malloc(sizeof(bexp_not));
  if (b == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_not_new: allocation failure.");
    exit(1);
  }
  b->e1 = e1;
  p->tag = NOT;
  p->e.not = b;
  return p;
}

/* free the expression and all its subexpressions */
void bexp_free(bexp *t)
{
  switch(t->tag)
  {
    case BCONST: break;

    case AND: bexp_free(t->e.and->e1);
              bexp_free(t->e.and->e2);
              free(t->e.and);
              break;

    case OR:  bexp_free(t->e.or->e1);
              bexp_free(t->e.or->e2);
              free(t->e.or);
              break;

    case NOT: bexp_free(t->e.not->e1);
              free(t->e.not);
  }
  free(t);
  return;
}

/* count the constants in a bexp tree */
/* (BTRUE and BFALSE are the only constants) */
unsigned int bexp_n_consts(bexp *t)
{
  switch(t->tag)
  {
    case BCONST: return 1;

    case AND: return bexp_n_consts(t->e.and->e1) +
                     bexp_n_consts(t->e.and->e2);

    case OR: return bexp_n_consts(t->e.or->e1) +
                    bexp_n_consts(t->e.or->e2);

    case NOT: return bexp_n_consts(t->e.not->e1);
  }
  fprintf(stderr, "%s\n", "bexp_n_consts: bexp tag unrecognized.");
  exit(1);
}

/* evaluate the expression to either BTRUE or BFALSE */
/* we leveage the fact that BFALSE == 0 and BTRUE == 1 */
bool bexp_eval(bexp *t)
{
  bool result1;
  bool result2;
  switch(t->tag)
  {
    case BCONST: return t->e.bconst == BTRUE ? BTRUE: BFALSE;

    case AND: result1 = bexp_eval(t->e.and->e1) == BTRUE;
              result2 = bexp_eval(t->e.and->e2) == BTRUE;
              return result1 && result2 ? BTRUE: BFALSE;

    case OR:  result1 = bexp_eval(t->e.or->e1) == BTRUE;
              result2 = bexp_eval(t->e.or->e2) == BTRUE;
              return result1 || result2 ? BTRUE: BFALSE;

    case NOT: return bexp_eval(t->e.not->e1) == BTRUE ? BFALSE: BTRUE;
  }
  fprintf(stderr, "%s\n", "bexp_eval: bexp tag unrecognized.");
  exit(1);
}

/* returns a fresh heap allocated true or false string */
char *bool_tos(bool bconst)
{
  char *t = "true";
  char *f = "false";
  if (bconst)
    return strdup(t);
  else
    return strdup(f);
}

/* generate the Racket equivalent of the expression */
/* - must return a fresh heap-allocated string */
char *bexp_to_rkt(bexp *t)
{
  char buf[512];

  //store the results from before and free them
  //after they've been copied into buf.
  char *tmp1 = NULL;
  char *tmp2 = NULL;

  switch(t->tag)
  {
    case BCONST:  tmp1 = bool_tos(t->e.bconst);
                  sprintf(buf, "%s", tmp1);
                  free(tmp1);
                  break;

    case AND: tmp1 = bexp_to_rkt(t->e.and->e1);
              tmp2 = bexp_to_rkt(t->e.and->e2);
              sprintf(buf, "(and %s %s)", tmp1, tmp2);
              free(tmp1);
              free(tmp2);
              break;

    case OR:  tmp1 = bexp_to_rkt(t->e.or->e1);
              tmp2 = bexp_to_rkt(t->e.or->e2);
              sprintf(buf, "(or %s %s)", tmp1, tmp2);
              free(tmp1);
              free(tmp2);
              break;

    case NOT: tmp1 = bexp_to_rkt(t->e.not->e1);
              sprintf(buf, "(not %s)", tmp1);
              free(tmp1);
              break;

    default:  fprintf(stderr, "%s\n", "bexp_to_rkt: bexp tag unrecognized.");
              exit(1);
  }

  char *p = strdup(buf);

  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "bexp_to_rkt: allocation failure.");
    exit(1);
  }

  return p;
}

int main()
{
  printf("%s\n", "Test 1");
  bexp *btrue1 = bexp_const_new(BTRUE);
  bexp *btrue2 = bexp_const_new(BTRUE);
  bexp *bfalse1 = bexp_const_new(BFALSE);
  bexp *bnot1 = bexp_not_new(btrue1);
  bexp *bnot2 = bexp_not_new(bfalse1);
  bexp *bnot3 = bexp_not_new(bnot2);
  bexp *bor1 = bexp_or_new(btrue2, bnot1);
  bexp *band1 = bexp_and_new(bor1, bnot3);

  char *rktstr = bexp_to_rkt(band1);

  printf("Expecting (and (or true (not true)) (not (not false))):\n%s\n", rktstr);
  bool result = bexp_eval(band1);
  printf("Expecting BFALSE: %s\n", result == BTRUE? "BTRUE":"BFALSE");
  printf("Expecting 3: The number of constants is %d\n", bexp_n_consts(band1));


  printf("%s\n", "Valgrind test here.");
  bexp_free(band1);
  free(rktstr);

  printf("%s\n", "Test 2");
  btrue1 = bexp_const_new(BTRUE);
  btrue2 = bexp_const_new(BTRUE);
  bexp *btrue3 = bexp_const_new(BTRUE);
  bfalse1 = bexp_const_new(BFALSE);
  bexp *bfalse2 = bexp_const_new(BFALSE);
  bor1 = bexp_or_new(btrue1, bfalse1);
  bnot1 = bexp_not_new(bor1);
  bnot2 = bexp_not_new(bfalse2);
  bexp *bor2 = bexp_or_new(btrue2, bnot2);
  band1 = bexp_and_new(bor2, btrue3);
  bexp *band2 = bexp_and_new(bnot1, band1);

  rktstr = bexp_to_rkt(band2);
  char *expected = "(and (not (or true false)) (and (or true (not false)) true))";
  printf("Expecting %s: \n %s \n", expected, rktstr);

  result = bexp_eval(band2);
  printf("Expecting BFALSE %s\n", result == BTRUE ? "BTRUE":"BFALSE" );
  printf("Expecting 5: The number of constants is %d\n", bexp_n_consts(band2));

  printf("%s\n", "Valgrind test here.");
  bexp_free(band2);
  free(rktstr);

}
