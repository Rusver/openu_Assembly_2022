#include "parcer.h"


int first_read(FILE *fptr)
{
	char buffer[BUFF_LEN];
	char** list = NULL;
	char*** macro_commands = NULL;
	int macro_counter = 0;
	char* macro_name;
	int list_len = 0;
	int macro_len = 0;
	
	macro_commands = (char***)malloc((sizeof(char*)));

	printf("YOU ARE IN THE FIRST READ");
	while (fgets(buffer, BUFF_LEN, fptr))
	{
		list = (char**)malloc((sizeof(char*)));
		printf("%s", buffer);
		get_input(buffer, list, &list_len);
		if (list && macro_handler(list) == 1 || macro_counter)
		{
			if (is_end_of_macro(list, list_len))
			{
				macro_len = macro_counter;
				macro_counter = -1;
			}
			else if (macro_counter == 0)
			{
				macro_name = (char*)malloc(strlen(list[1]));
				strncpy(macro_name, list[1], strlen(list[1])+1);
				macro_name[strcspn(macro_name, "\n")] = 0;
			}
			else
			{			
				macro_commands[macro_counter - 1] = (char**)malloc((sizeof(char*)));
				macro_commands[macro_counter - 1] = list;
			}
			macro_counter += 1;
			
			
		}
		free_list(list, list_len);
	}




	return 1;
}

int second_read(FILE *fptr)
{

	return 1;
}


int macro_handler(char** list)
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
