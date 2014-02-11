#include <stdio.h>
#include "expt.h"

void evidence_expt()
{
  printf("Tests for expt\n");
  printf("Expecting 1024: %ld\n", expt(2,10));  /* 1024 */
  printf("Expecting 134217728: %ld\n", expt(8,9));   /* 134217728 */
  printf("Expecting 96059601: %ld\n", expt(99,4));  /* 96059601 */
  printf("Expecting 184528125: %ld\n", expt(45,5));  /* 184528125 */
}

void evidence_ss()
{
  printf("Tests for ss\n");
  printf("Expecting 1024: %ld\n", ss(2,10));    /* 1024 */
  printf("Expecting 134217728: %ld\n", ss(8,9));   /* 134217728 */
  printf("Expecting 96059601: %ld\n", ss(99,4));    /* 96059601 */
  printf("Expecting 184528125: %ld\n", ss(45,5));    /* 184528125 */
}

void evidence_ssm()
{
  printf("Tests for ssm\n");
  printf("Expecting 24: %d\n", ssm(2,10, 1000));  /* 24 */
  printf("Expecting 728: %d\n", ssm(8,9, 1000));   /* 728 */
  printf("Expecting 1: %d\n", ssm(99,4, 100));   /* 1 */
  printf("Expecting 8125: %d\n", ssm(45,5, 10000)); /* 8125 */
}

int main(int argc, char *argv[])
{
  evidence_expt();
  evidence_ss();
  evidence_ssm();
  return 0;
}
