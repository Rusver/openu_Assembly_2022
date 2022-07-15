#include "parcer.h"


int first_read(FILE *fptr)
{
	char buffer[BUFF_LEN];

	printf("YOU ARE IN THE FIRST READ");
	while (fgets(buffer, BUFF_LEN, fptr))
	{
		printf("%s", buffer);
		get_input(buffer);
	}

	return 1;
}

int second_read(FILE *fptr)
{

	return 1;
}


void macro_handler()
{

}

int get_input(char* line)
{

	return 1;
}