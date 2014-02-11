//Victor Cheung, Vcheung
//CS152, Win14
//Homework 3, Problem 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// cat concatenates two strings
// and locates the newly created string in the heap.
//cat returns the pointer to the new string.
char *cat(char *s1, char *s2)
{
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  char *p = malloc((len1 + len2 + 1) * sizeof(char));
  int i;
  for (i = 0; s1[i] != '\0'; i++)
  {
    p[i] = s1[i];
  }
  for(i = 0; s2[i] != '\0'; i++)
  {
    p[i + len1] = s2[i];
  }
  p[len1 + len2] = '\0';
  return p;
}
//catw concatenates two strings with a separator in between
// and locates the newly created string in the heap.
//catw returns the pointer to the new string.
char *catw(char *s1, char sep, char *s2)
{
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  char *p = malloc((len1 + len2 + 2) * sizeof(char));
  int i;
  for (i = 0; s1[i] != '\0'; i++)
  {
    p[i] = s1[i];
  }
  p[i] = sep;
  for(i = 0; s2[i] != '\0'; i++)
  {
    p[i + len1 + 1] = s2[i];
  }
  p[len1+len2+1] = '\0';
  return p;
}
//catw_arr concatenates all the strings in a string array
// with a separator inbetween each string
//catw_arr returns a pointer to the concatenated string.
char *catw_arr(char *ss[], int slen, char sep)
{
  int i, j, index = 0, sum = 0;
  for (i = 0; i < slen; i++)
  {
    sum += strlen(ss[i]);
  }
  char *p = malloc( (sum + slen)  * sizeof(char));
  for (i = 0; i < slen; i++)
  {
    for (j = 0; ss[i][j] != '\0'; j++)
    {
      p[index++] = ss[i][j];
    }
    if (index != (sum + slen - 1))
      p[index++] = sep;
  }
  p[(sum + slen - 1)] = '\0';
  return p;
}
//displays a string as an array of chars
//prints out \0 as last element of array if
//it's in the string
void display(char *p)
{
  char c;
  int i = 0;
  printf("[");
  while ((c = p[i++]) != '\0')
    printf("%c ", c);
  if (p[--i] == '\0')
    printf("\\0");
  printf("]\n");
}

//manual testing
int main (int argc, char **argv)
{
  char *p1_arr[] = {"om", "ef", "lol," "gb", "" };
  char *p1 = catw_arr(p1_arr, 3, ',');
  printf("%s\n", p1);
  display(p1);
}
