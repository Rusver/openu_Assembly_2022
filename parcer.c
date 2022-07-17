#include "parcer.h"


int first_read(FILE *fptr)
{
	char tst[50] = "hello";
	char* test = NULL;
	char** list_of_macros_names = NULL;
	char**** macro_commands = NULL;
	int list_len = 0;

	test = tst;
	list_of_macros_names = &test;


	macro_commands = (char****)malloc((sizeof(char*)));
	macro_commands[0] = (char***)malloc((sizeof(char*)));
	macro_commands[0][0] = list_of_macros_names;
	macro_commands[0][1] = list_of_macros_names;
	macro_commands[1] = (char***)malloc((sizeof(char*)));
	macro_commands[1][1] = list_of_macros_names;


	printf("YOU ARE IN THE FIRST READ");

	list_of_macros_names = macro_handler(fptr, &list_len, macro_commands);
	printf("list");
	rewind(fptr);



	/*free_list(list_of_macros_names);*/
	return 1;
}


int second_read(FILE *fptr)
{

	return 1;
}


int is_macro(char** list)
{
	if (!strncmp(list[0], "macro", strlen("macro")))
		return 1;
	else
		return 0;
}

int is_end_of_macro(char** list, int list_len)
{
	int i;
	for (i = 0; list_len > i; i++)
	{
		if (!strncmp(list[i], "endmacro", strlen("endmacro")))
			return 1;
	}
	return 0;
}

void get_input(char* line, char** list, int *idx)
{
	char * token;
	*idx = 0;
	token = strtok(line, " "); /*extract the first token*/
	/* loop through the string to extract all other tokens */
	while (token != NULL)
	{
		if (token && token[0] == '\t')
			memmove(token, token + 1, strlen(token));
		printf("%s\n", token); 
		list[*idx] = (char *)malloc(strlen(token)+1);
		strncpy(list[*idx], token, strlen(token)+1);
		token = strtok(NULL, " "); /*get every token*/
		(*idx)++;
	}
	if (*idx == 0)
		list = NULL;
}
