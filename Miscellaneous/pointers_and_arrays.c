#include <stdio.h>

//ENTER ./a.out Hello There in terminal.

int main(int argc, char **argv)
{
	int i,j;
	char c;
	printf("%c\n", **argv); //outputs .
	printf("%c\n", *argv[0]); //outputs .
	printf("%c\n", (*argv)[1]); //outputs /
	printf("%c\n", *((*argv)+1)); //outputs /
	printf("%c\n", *argv[1]); //outputs H
	printf("%s\n", *argv); //outputs ./a.out
	printf("%s\n", *(argv + 1)); //outputs Hello
	printf("%d %d\n", argv, argv + 1); //different between numbers will be 8 on a 64 						   //bit system and 4 on a 32 bit system. This is
					   //due to the size of pointers in memory.

	printf("\n");
	char badstring[] = {'a', 'b', 'c'};

	for (i = 1; i < argc; i++)
	{
		for (j = 0; (c = argv[i][j]) != '\0'; j++)
			putchar(c);
		printf("%s", argv[i]);s
		printf("%s", badstring);
		printf("\n");
	}
}

/* argv is a really a two dimensional array; the first array *argv contains pointers to
* the strings (which are just character arrays).
* i starts at 1 since the first value in the argv array is the name of the executable
* *argv[1] outputs H since [] has higher precedence than *.
* (*argv)[1] is equivalent to *((*argv)+1) and forces the compiler to evaluate the value
* of the first object in the array (which it finds to be an array).
* Adding *(argv + i) refers to argv[i]. That is, it shifts from the 0th element to the ith
* element of the array of objects it's pointing to, in this case an array of char *
* pointers.
* Pointers have different sizes depending on the OS. 64bit systems have 8 byte pointer
* usually and 32bit systems have 4 byte pointers usually.
* Pointer arithmetic really refers to how C does math with pointers. Adding 1 to a  *pointer is equivalent to adding the size of the data type to which it points to the
* address of the first object.
* Pointers always store the adress of the first byte of the object to which it points.
*/

