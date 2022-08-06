#include "pre_and_parcer.h"

int first_read(FILE *fptr)
{

	char** list_of_macros_names = NULL;
	char**** macro_commands = NULL;
	int name_list_len = 0;
    int macro_list_len = 0;

    macro_commands = malloc(sizeof(char*));
    *macro_commands = malloc(sizeof(char*));
    **macro_commands = malloc((sizeof(char*)));


    /*
	macro_commands[0][0] = list_of_macros_names;
	macro_commands[0][1] = list_of_macros_names;
	macro_commands[1] = (char***)malloc((sizeof(char*)));
	macro_commands[1][1] = list_of_macros_names;
    */

	printf("YOU ARE IN THE FIRST READ");

	list_of_macros_names = macro_handler(fptr, &name_list_len, &macro_commands, &macro_list_len);
	printf("list");
	rewind(fptr);

    write_expanded_file(fptr, list_of_macros_names, macro_commands, &name_list_len, &macro_list_len);


    /*free_list(**macro_commands);*/
    /*free_list(*macro_commands);*/
    free(macro_commands);
	return 1;
}


int second_read()
{

    FILE *fptr;

    fptr = fopen("extended.as", "r");
    if (!fptr) /* If the wasn't found, or it isn't allowed for reading, the file pointer is NULL */
    {
        fprintf(stderr, "Couldn't open file extended\n");
    }

    label_handler(fptr);

    rewind(fptr);

    assembler(fptr);




	return 1;
}

int is_label(char* list)
{
    int len = strlen(list) -1;
    if (list[len] == ':')
        return 1;
    return 0;

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

void get_input(char* line, char*** list, int *idx)
{
	char *token;
    char* local_line;
    char **list_local = *list; /* Make things easier by avoiding one * within the function.*/
    char **temp = NULL;

	*idx = 0;

    local_line = malloc(strlen(line));
    strcpy(local_line, line);

	token = strtok(local_line, " "); /*extract the first token*/
	/* loop through the string to extract all other tokens */
	while (token != NULL)
	{
		if (token[0] == '\t')
			memmove(token, token + 1, strlen(token));

		printf("%s\n", token);

        list_local[*idx] = malloc(strlen(token)+1);
		strcpy(list_local[*idx], token);
		token = strtok(NULL, " ");   /*get every token*/
		(*idx)++;

        /* Increase array size to hold 1 more entry. */
        temp = realloc(list_local, sizeof(char*) * (*idx + 1));
        if (temp != NULL)
            list_local = temp;

	}
	if (*idx != 0)
        list_local[*idx - 1][strcspn(list_local[*idx - 1], "\n")] = 0; /* remove the "\n" */

    list_local[*idx] = NULL; /*to know when the list ends */
    *list = list_local;
}

int has_macro(char** list_of_macros_names, char** list, int* name_list_len, int* list_len)
{
    int macro_len = 0;

    int i = 0;

    for(i =0; i < *name_list_len; i++)
    {
            if (list_of_macros_names[i] && list[0])
            {
                if (!strncmp(list_of_macros_names[i], list[0],
                             strlen(list_of_macros_names[i])))
                {
                    return 1;
                }
            }
        macro_len++;
    }
    return 0;
}

void free_list(char** list)
{
    int i=0;
    while (list[i])
    {
        free(list[i]);
        i++;
    }
}

