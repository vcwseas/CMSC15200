// Victor Cheung, vcheung
// CMSC 152, Win 14
// Lab6

#include "tele.h"

//num to telegram num conversion table
char num_table[] = {'O', 'I', 'Z', 'B', '4', 'S', '6', 'T', '8', '9'};

//converts a character from ASCII to the Telegram equivalent
char convert_char(char c)
{
  if (c >= 'A' && c <= 'Z')
    return c;
  else if (c >= 'a' && c <= 'z')
    return c - 'a' + 'A';
  else if (c >= '0' && c <= '9')
    return num_table[c - '0'];
  else if (c == '?')
    return c;
  else if (c == ' ' || c == '\t' || c == '\n')
    return ' ';
  else
    //sentinel value used for omitting
    return '!';
}

//converts an ASCII string to the Telegram equivalent with consecutive
//spaces removed from the final string.
char *ascii_to_tgm(char *msg)
{
  char *buf = strdup(msg);
  if (buf == NULL)
  {
    fprintf(stderr, "%s\n", "ascii_to_tgm: allocaton failure.");
    exit(1);
  }
  char *buf_index = buf;
  char *tmp3 = buf;
  char c;

  //first run-through: converts to equivalent or discards
  while (*msg != '\0')
  {
    if ((c = convert_char(*msg)) == '!')
      msg++;
    else
    {
        *buf_index = c;
        msg++;
        buf_index++;
    }
  }
  *buf_index = '\0';

  //second run-through: removes consecutive white spaces

  char *buf2 = strdup(buf);
  if (buf2 == NULL)
  {
    fprintf(stderr, "%s\n", "ascii_to_tgm: allocaton failure.");
    exit(1);
  }
  char *buf2_index = buf2;
  int counter = 0;
  while (*tmp3 != '\0')
  {
    if (*tmp3 == ' ' && *(tmp3+1) != '\0' && *(tmp3+1) == ' ')
      tmp3++;
    else
    {
      *buf2_index = *tmp3;
      buf2_index++;
      tmp3++;
      counter++;
    }
  }

  *buf2_index = '\0';

  char *buf3 = malloc(sizeof(char) * ++counter);
  if (buf3 == NULL)
  {
    fprintf(stderr, "%s\n", "ascii_to_tgm: allocaton failure.");
    exit(1);
  }
  memcpy(buf3, buf2, counter);
  free(buf2);
  free(buf);
  return buf3;
}


// int main()
// {

//   char *t1 = "When were you born?  I was born long ago, in 1809.";
//   char *t2 = "M ! ! ! ! ! ! ! !? \t \t \t \t \n \n \n !!!!!?    ?       ";
//   char *t3 = "That's right. My name is actually that. ,./;'[]-='| ? 1234567890";
//   char *t4 = "THIS IS A TEST STRING THAT IS ALREADY TELEGRAM OIZB4S6T89";
//   char t5[] = {'a', 'b', '.', '\t', '0','e', '\0'};
//   char *t6 = malloc(20*sizeof(char));
//   memcpy(t6, t1, 19);
//   t6[19] = '\0';

//   printf("%s\n", ascii_to_tgm(t1));
//   printf("length reduction of %lu\n", strlen(t1) - strlen(ascii_to_tgm(t1)));
//   printf("%s\n", ascii_to_tgm(t2));
//   printf("length reduction of %lu\n", strlen(t2) - strlen(ascii_to_tgm(t2)));
//   printf("%s\n", ascii_to_tgm(t3));
//   printf("length reduction of %lu\n", strlen(t3) - strlen(ascii_to_tgm(t3)));
//   printf("%s\n", ascii_to_tgm(t4));
//   printf("length reduction of %lu\n", strlen(t4) - strlen(ascii_to_tgm(t4)));
//   printf("%s\n", ascii_to_tgm(t5));
//   printf("length reduction of %lu\n", strlen(t5) - strlen(ascii_to_tgm(t5)));
//   printf("%s\n", ascii_to_tgm(t6));
//   printf("length reduction of %lu\n", strlen(t6) - strlen(ascii_to_tgm(t6)));
//   return 0;
// }

