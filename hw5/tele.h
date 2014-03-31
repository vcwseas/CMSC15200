#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


//converts a character from ASCII to the Telegram equivalent
char convert_char(char c);

//converts an ASCII string to the Telegram equivalent with consecutive
//spaces removed from the final string.
char *ascii_to_tgm(char *msg);
