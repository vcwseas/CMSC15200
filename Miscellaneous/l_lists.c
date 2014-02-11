//Lists Functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>



typedef struct list list;
struct list {
  int v;
  list *next;
};


list *list_new(int v, list *next)
{
  list *p = malloc(sizeof(list));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "list_new: allocation failed");
    exit(1);
  }
  p->v = v;
  p->next = next;
  return p;
}

int is_empty(list *l)
{
  return l == NULL;
}

int first(list *l)
{
  if (l == NULL)
  {
    fprintf(stderr, "%s\n", "first: Null pointer error");
    exit(1);
  }
  return l->v;
}

list *rest(list *l)
{
  if (l == NULL)
  {
    fprintf(stderr, "%s\n", "rest: null pointer error");
    exit(1);
  }
  return l->next;
}

int sum(list *l)
{
  int s;
  for (s = 0; l != NULL; l = l->next)
    s += l->v;
  return s;
}

int length(list *l)
{
  int i;
  for (i = 0; l != NULL; l = l->next)
    i++;
  return i;
}

list *cons(int v, list *l)
{
  list *p = malloc(sizeof(list));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "cons: allocation failed");
    exit(1);
  }
  p->v = v;
  p->next = l;
  return p;
}

void list_show(list *l)
{
  while (l != NULL)
  {
    printf("%d ", l->v);
    l = l->next;
  }
  printf("\n");
}

void map(int (*func)(int), list *l)
{
  while (l != NULL)
  {
    l->v = func(l->v);
    l = l->next;
  }
}

int twice_that(int a)
{
  return a * 2;
}

//displays a list


//given a list and an int, return the number of times
// that int occurs in the list.
int count(list *l, int target)
{
  int count = 0;
  if (l == NULL)
    return count;
  else
  {
    for (;l != NULL; l=l->next)
    {
      if (l->v == target)
        count++;
    }
    return count;
  }
}

// Given a list and an index, return the data
// in the nth node of the list. The nodes are numbered from 0.
// Assert fails if the index is invalid (outside 0..length-1).
int get_nth(list *l,  int n)
{
  int i;
  if (n < 0) {fprintf(stderr, "%s\n", "index must be larger than one"); exit(1);}
  if (l == NULL){ fprintf(stderr, "%s\n", "get_nth: empty list"); exit(1);}
  for (i = 0; l != NULL; l = l->next)
  {
    if (i == n)
      return l->v;
    i++;
  }
  fprintf(stderr, "%s\n", "get_nth: element not found");
  assert(l != NULL);
}

//deallocates all memory and sets head pointer to NULL
void delete_list(list **l)
{
  list *h = *l;
  if (h == NULL)
    return;
  else
  {
    list *tmp;
    while (h->next != NULL)
    {
      tmp = h->next;
      free(h);
      h = tmp;
    }
    free(h);
    *l = NULL;
  }
}

int pop(list **l)
{
  list *p = *l;
  *l = p->next;
  int v = p->v;
  free(p);
  return v;
}

//returns a pointer to the ith element in a list.
list *ith_element(list *l, int i)
{
  int j;
  for (j = 0; l != NULL; l = l->next)
    if (j++ == i)
      return l;
  fprintf(stderr, "%s\n", "ith_element: index exceeds list.");
  return NULL;
}

//inserts a new node at the index position of a list
//range of index is [0...length].
void insert_nth(list **l, int index, int v)
{
  if (*l == NULL)
  {
    *l = cons(v, NULL);
    return;
  }
  if (index == 0)
  {
    *l = cons(v, *l);
    return;
  }
  list *p = ith_element(*l, index - 1);
  if (p == NULL)
    { fprintf(stderr, "%s\n", "insert_nth: out of bounds."); exit(1); }
  p->next = cons(v, p->next);
  return;
}

//in a sorted ascending list, inserts a new node
//at the correct position in the list
void sorted_insert(list **l, list *n)
{
  if (l == NULL || n == NULL)
  {
    fprintf(stderr, "%s\n", "sorted_insert: arg is null");
    exit(1);
  }
  //where you have an empty list
  if (*l == NULL)
  {
    *l = n;
    return;
  }
  //where n is inserted at the 0th position
  //is a special case
  if (n->v < (*l)->v)
  {
    n->next = *l;
    *l = n;
    return;
  }
  //normal cases (where *l is not modified)
  list *pb = *l;
  list *p = (*l)->next;
  while (p != NULL)
  {
    if (n->v < p->v)
    {
      n->next = p;
      pb->next = n;
      return;
    }
    pb = p;
    p = p->next;
  }
  //if p == NULL then we insert at the last position
  pb->next = n;
  n->next = NULL;
  return;
}

//given a list, sorts it into increasing order
void insert_sort(list **l)
{
  if (l == NULL)
  {
    fprintf(stderr, "%s\n", "insert_sort: NULL pointer error");
    exit(1);
  }
  if (*l == NULL)
    return;

  list *node = *l;
  list *tmp;
  while(node->next != NULL)
  {
    tmp = node->next;
    node->next = NULL;
    sorted_insert(l, node);
    node = tmp;
  }
  sorted_insert(l, node);
}
//takes two lists and appends the latter onto the first
void append(list **l1, list **l2)
{
  if (*l1 == NULL)
  {
    *l1 = *l2;
    *l2 = NULL;
    return;
  }
  list *p = *l1;
  while(p->next != NULL)
  {
    p = p->next;
  }
  p->next = *l2;
  *l2 = NULL;
  return;
}

//given a list, splits it in half
//if ood, the extra element in mid goes to front list
void split(list *ref, list **front, list **back)
{
  //if list is empty, there is nothing to split.
  if(ref == NULL) {*front = NULL; *back = NULL; return;}

  *front = ref;

  //if list is of length 1
  if (ref->next == NULL) {*back = NULL; return;}

  list *fast = ref, *slow = ref;
  while (fast->next != NULL)
  {
    fast = fast->next;
    if (fast->next == NULL)
      break;
    fast = fast->next;
    slow = slow->next;
  }
  *back = slow->next;
  slow->next = NULL;
  return;
}



//removes duplicates from a SORTED list
void remove_sorted_dup(list *l)
{
  while(l->next != NULL)
  {
    list *tmp = l->next;
    if (l->v == tmp->v )
    {
      l->next = tmp->next? tmp->next : NULL;
      free(tmp);
    }
    if(l->next && (l->next->v != l->v))
      l = l->next;
  }
  return;
}

//moves the front node of the second list onto the head
//of the first list
void move_node(list **dest, list **source)
{
  if (*source == NULL) {fprintf(stderr, "%s\n", "move_node: source is empty."); exit(1);}
  list *source_tmp = *source;
  *source = (*source)->next;
  source_tmp->next = *dest;
  *dest = source_tmp;
  return;
}

//reverses a list
void reverse(list **l)
{
  list *tmp;
  list *prev = NULL;
  list *head = *l;
  while (head != NULL)
  {
    tmp = head->next;
    head->next = prev;
    prev = head;
    head = tmp;
  }
  *l = prev;
  return;
}

//splits the list such that the elements at positions 0, 2, 4..
//are in the A list; and 1, 3, 5.. are in the B list.
void alternating_split(list **source, list **A, list **B)
{
  if (*source == NULL) {*A = NULL; *B = NULL; return;}
  if ((*source)->next == NULL) {*A = *source; *B = NULL; return;}
  int alt = 1;
  while (*source != NULL)
  {
    if (alt)
      move_node(A, source);
    else
      move_node(B, source);
    alt = !alt;
  }
  return;
}

//merges two lists alternatively, starting with the first
void alternating_merge(list **dest, list **A, list **B)
{
  //if A is empty, dest is just B
  if (*A == NULL) {*dest = *B; return;}
  //if B is empty, dest is just A
  if (*B == NULL) {*dest = *A; return;}

  //dummy node
  list *node1 = *A;
  list *node2 = *B;
  list *tmp, *tmp2;
  //the destination always begins with the first of the A list
  *dest = *A;
  while (node1->next != NULL && node2->next != NULL)
  {
    //move two dummy nodes down the list
    //reattaching pointers along the way
      tmp = node1->next;
      node1->next = node2;
      tmp2 = node2->next;
      node2->next = tmp;
      node1 = tmp;
      node2 = tmp2;
  }
  //case where list A is shorter than list B
  if (node1->next == NULL && node2->next != NULL)
    node1->next = node2;
  //case where list B is shorter than list A
  else if (node2->next == NULL && node1->next != NULL)
  {
    tmp = node1->next;
    node1->next = node2;
    node1->next->next = tmp;
  }
  else
  //case where they're the same length
    node1->next = node2;
  //both A and B should not point to anything anymore
  *A = NULL;
  *B = NULL;
  return;
}


//take two sorted increasing lists and returns
//a combined sorted increasing list
//use move_node?
list *sorted_merge(list *A, list *B)
{
  list *p;
  if (A == NULL || B == NULL)
  {
      p = A? B : A;
      return p;
  }
  while(A->next != NULL && B->next != NULL)
  {

  }

}


int main(int argc, char **argv)
{

  list *p;
  list *f = NULL;
  list *s = NULL;
  int i;

  for (i = 0; i < 10; i++)
  {
    s = cons(i, s);
  }
  list_show(f);
  list_show(s);

  alternating_merge(&p, &f, &s);
  list_show(p);
  list_show(f);
  list_show(s);


}

