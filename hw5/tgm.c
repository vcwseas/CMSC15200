// Victor Cheung, VCheung
// CMSC 15200, Win-14
// HW5, Telegram

#include "tele.h"
typedef unsigned char byte;

//n_chars is the number of characters in the packed message
typedef struct {
  unsigned int n_chars;
  byte *packed;
} tgm_packed;

unsigned int num_bytes(unsigned int n_chars)
{
  return (unsigned int) ceil((n_chars * 5)/8.0);
}

//displays a bit vector based on each byte.
void packed_show(tgm_packed* p)
{
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "packed_show: parameter is NULL.");
    exit(1);
  }
  unsigned int i, j;
  unsigned int n_bytes = num_bytes(p->n_chars);
  for (i = 0; i < n_bytes; i++)
  {
    printf("%dth byte: ", i);
    for (j = 0; j < 8; j++)
    {
      printf("%c", p->packed[i] & (1 << (8 - j - 1)) ? '1' : '0');
    }
    printf("\n");
  }
}

//i is the index of the bit
byte packed_get(byte *p, unsigned int i)
{
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "packed_get: parameter is NULL.");
    exit(1);
  }
  unsigned int byte_index = i / 8;
  unsigned int bit_index = i % 8;
  return p[byte_index] & (1 << (8 - bit_index - 1)) ? 1 : 0;
}

//sets a bit in a bit vector
//i is the index of the bit
//val will be either 0 or 1
void packed_set(byte *p, unsigned int i, unsigned int val)
{
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "packed_set: paramter is NULL.");
    exit(1);
  }
  unsigned int byte_index = i / 8;
  unsigned int bit_index = i % 8;
  if (val == 0)
  {
    p[byte_index] &= ~(1 << (8 - bit_index - 1));
  }
  else if (val == 1)
  {
    p[byte_index] |= (1 << (8 - bit_index - 1));
  }
  else
  {
    fprintf(stderr, "%s\n", "packed_set: parameter out of bounds.");
    exit(1);
  }
}

//returns a new tgm_packed with the desired n_chars
//and appropriately sized bitarray initialized to zero
//for all bits.
tgm_packed *tgm_packed_new(unsigned int n_chars)
{
  tgm_packed *p = malloc(sizeof(tgm_packed));
  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "tgm_packed_new: alocation failure.");
    exit(1);
  }
  p->n_chars = n_chars;
  unsigned int n_bytes = num_bytes(n_chars);
  p->packed = malloc(n_bytes * sizeof(byte));
  unsigned int i;
  for (i = 0; i < n_bytes; i++)
  {
    p->packed[i] = 0;
  }
  return p;
}

//convert from character to tgm table value
byte num_val(byte c)
{
  switch (c)
  {
    case ' ': return 26;
    case '?': return 27;
    case '4': return 28;
    case '6': return 29;
    case '8': return 30;
    case '9': return 31;
    default: return c - 'A';
  }
}

//convert from tgm table value to character
char char_val(byte c)
{
  switch(c)
  {
    case 26: return ' ';
    case 27: return '?';
    case 28: return '4';
    case 29: return '6';
    case 30: return '8';
    case 31: return '9';
    default: return c + 'A';
  }
}

//packs a string of tgm format
//according to tgm compression
//based on tgm table
tgm_packed *tgm_pack(char *tgm)
{
  if (tgm == NULL)
  {
    fprintf(stderr, "%s\n", "tgm_pack: parameter is NULL");
    exit(1);
  }
  tgm_packed *t = tgm_packed_new(strlen(tgm));

  unsigned int packed_index = 0;
  unsigned int tgm_index;
  byte c;
  while (*tgm != '\0')
  {
    c = num_val(*(tgm++));
    for (tgm_index = 3; tgm_index < 8; tgm_index++)
    {
      packed_set(t->packed, packed_index++, packed_get(&c, tgm_index));
    }
  }
  return t;
}

//unpacks a tgm_pack struct
//outputs a string of tgm format
char *tgm_unpack(tgm_packed *t)
{
  if (t == NULL)
  {
    fprintf(stderr, "%s\n", "tgm_unpack: paramter is NULL");
    exit(1);
  }

  // extra slot for '\0'
  char *p = malloc(t->n_chars + 1);

  if (p == NULL)
  {
    fprintf(stderr, "%s\n", "tgm_unpacked: allocation fialure.");
    exit(1);
  }

  unsigned int packed_index = 0;
  unsigned int char_index = 0;
  unsigned int tmp_index;
  byte tmp;
  unsigned int bit_bound = t->n_chars * 5;

  while(packed_index < bit_bound)
  {
    tmp = 0;
    for (tmp_index = 3; tmp_index < 8; tmp_index++)
    {
      packed_set(&tmp, tmp_index, packed_get(t->packed, packed_index++));
    }
    p[char_index++] = char_val(tmp);
  }

  //terminal character here
  p[char_index] = '\0';
  return p;
}

void tgm_free(tgm_packed *t)
{
  free(t->packed);
  free(t);
}


int main()
{
  char *test_string = "WXYZABCD";
  char *tmp;
  tgm_packed *t = tgm_pack((tmp = ascii_to_tgm(test_string)));
  // unsigned int n_bytes = (unsigned int) ((t->n_chars * 5) / 8.0 + 0.5);
  // for (unsigned int i = 0; i < n_bytes; i++)
  // {
  //   printf("%d\n", t->packed[i]);
  // }
  char *test_result = tgm_unpack(t);
  printf("%s\n", test_result);
  free(tmp);
  tgm_free(t);
  free(test_result);

  char *t2 = "hello 12  345  6   789 0";
  tgm_packed *t3 = tgm_pack((tmp = ascii_to_tgm(t2)));
  char *t4 = tgm_unpack(t3);
  printf("%s\n", t4);
  free(tmp);
  tgm_free(t3);
  free(t4);

  char *t5 = "i'm a\t\t\t\n   test string? !@#$\%^&*() 1234567890[]\\';/.,`~";
  tgm_packed *t6 = tgm_pack((tmp = ascii_to_tgm(t5)));
  char *t7 = tgm_unpack(t6);
  printf("%s\n", t7);
  free(tmp);
  free(t7);
  tgm_free(t6);

  char *a = "   \t\t\t\n.,.,.,.,.,.,!!!!!0123456789 -- abcdefghijklmnopqrstuvwxyz -- ,./;'[]-=<>?:{}_+!@#$%^&*()\n\n\tDone.,.,.,.,.,.,.,.,.,.!!!!!";
  char *tmp2 = ascii_to_tgm(a);
  tgm_packed *b = tgm_pack(tmp2);
  char *c = tgm_unpack(b);
  printf("%s\n", c);
  free(c);
  free(tmp2);
  tgm_free(b);


  char *empty = "";
  char *e2 = ascii_to_tgm(empty);
  tgm_packed *b2 = tgm_pack(e2);
  char *e3 = tgm_unpack(b2);
  printf("%s\n", e3);
  free(e2);
  free(e3);
  tgm_free(b2);
  return 0;

}
