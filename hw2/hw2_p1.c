// Victor Cheung, vcheung
// CS 152, Winter 2014
// Homwork 2, Problem 1

#include <stdio.h>
#include <stdlib.h>

//prints a integer array in format [x1, x2, x3, ... ,  xn]
void ia_show(int a[], int len, int newline)
{
  int i;
  printf("[");
  for (i = 0; i < len; i++)
  {
    if (i == len - 1)
      printf("%d", a[i]);
    else
      printf("%d, ", a[i]);
  }
  printf("]");
  if (newline)
    printf("\n");
}

//returns the manimum element in the array
int ia_max(int a[], int len)
{
  if (len == 0)
  {
    fprintf(stderr, "ia_max: length of array is 0\n");
    exit(1);
  }
  int i, max = a[0];
  for (i = 0; i < len; i++)
  {
    if (a[i] > max)
      max = a[i];
  }
  return max;
}

//destructively reverses the given array
void ia_reverse(int a[], int len)
{
  int i, temp, target, mid = (len + 1) / 2;
  for (i = 0; i < mid; i++)
  {
    target = len - i - 1;
    temp = a[i];
    a[i] = a[target];
    a[target] = temp;
  }
}

//checks whether two arrays are exactly the same
int ia_same(int a[], int alen, int b[], int blen)
{
  if (alen != blen)
    return 0;
  else
  {
    int i;
    for (i = 0; i < alen; i++)
    {
      if (a[i] != b[i])
        return 0;
    }
  }
  return 1;
}



int main()
{
  int a[] = {1,2,3,4,5,6,7};
  int b[] = {3,2,1,4,5,6};
  int c[] = {};
  int d[] = {0,0,0,0,0,0};
  int e[] = {1,2,3,4,5,6,7};

  //TESTS for ia_max
  printf("%s\n", "Tests for ia_max");
  printf("%d\n", ia_max(a, 7));
  printf("%d\n", ia_max(b, 6));
  printf("%d\n", ia_max(d, 6));

  //TESTS FOR ia_reverse
  printf("%s\n", "Tests for ia_reverse");
  ia_show(a, 7, 1);
  ia_reverse(a, 7);
  ia_show(a, 7, 1);
  printf("\n");
  ia_show(b, 6, 1);
  ia_reverse(b, 6);
  ia_show(b, 6, 1);
  printf("\n");
  ia_show(d, 6, 1);
  ia_reverse(d, 6);
  ia_show(d, 6, 1);

  //TESTS FOR ia_same
  printf("%s\n", "Tests for ia_same" );
  ia_show(a, 7, 1);
  ia_show(b, 6, 1);
  printf("%d\n", ia_same(a, 7, b, 6));

  ia_show(e, 7, 1);
  ia_reverse(a, 7);
  ia_show(a, 7, 1);
  printf("%d\n", ia_same(a, 7, e, 7));

  //ERROR CHECKING
  printf("%s\n", "ERROR CHECKING");
  ia_reverse(c, 0);


  return 0;
}
