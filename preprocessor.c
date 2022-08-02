#include "pre_and_parcer.h"


char** macro_handler(FILE* fptr, int* name_list_len, char**** macro_commands, int* macro_list_len) /* return macro_counter */
{
	char buffer[BUFF_LEN];
	char** list = NULL;
	char** list_of_macros_names = NULL;
	char* macro_name;
	int list_len = 0;

	/*int line_count = 0;*/
	int initizilied_flag = 0;
	
	list_of_macros_names = (char**)malloc(sizeof(char*));

	while (fgets(buffer, BUFF_LEN, fptr))

	{
		list = malloc((sizeof(char*)));
		printf("%s", buffer);
		get_input(buffer, &list, &list_len);  /*by line*/
		if ((list && (is_macro(list)) == 1) || *macro_list_len)
		{
			if (is_end_of_macro(list, list_len))
            {
				*macro_list_len = -1;
			}
			else if (*macro_list_len == 0)
			{

				list_of_macros_names[*name_list_len] = (char*)malloc(strlen(list[1]));
				macro_name = list_of_macros_names[*name_list_len];
				strncpy(macro_name, list[1], strlen(list[1]) + 1);
				(macro_name)[strcspn(macro_name, "\n")] = 0;  /*delete \n in the macro name*/
				(*name_list_len)++;
				initizilied_flag = 0;
			}
			else
			{
				if (*name_list_len > 1 && initizilied_flag == 0)
				{
					macro_commands[*name_list_len - 1] = (char***)malloc(sizeof(char*));
					initizilied_flag = 1;
				}

                deep_copy_command_list(macro_commands, *name_list_len, *macro_list_len, list, list_len);
                /*macro_commands[*name_list_len - 1][*macro_list_len - 1][list_len] = NULL;*/
			}
			*macro_list_len += 1;


		}
        free_list(list);
        free(list);
	}
	
	return list_of_macros_names;
}

void deep_copy_command_list(char**** macro_commands, int name_list_len, int macro_list_len, char** list, int list_len)
{
    int i =0;
    macro_commands[name_list_len - 1][macro_list_len - 1] = (char**)malloc((sizeof(char*)));
    for (i =0; i < list_len; i++)
    {
        macro_commands[name_list_len - 1][macro_list_len - 1][i] = (char*)malloc(strlen(list[i])+1);
        strncpy(macro_commands[name_list_len - 1][macro_list_len - 1][i], list[i], strlen(list[i])+1);
    }
    macro_commands[name_list_len - 1][macro_list_len - 1][i] = NULL;

}

int write_expanded_file(FILE *fptr, char** list_of_macros_names, char**** macro_commands, int* name_list_len, int* macro_list_len)
{


    char buffer[BUFF_LEN];
    char** list = NULL;
    int list_len = 0;
    FILE* new_file = NULL;
    new_file = fopen("extended.as", "w");
    if(new_file == NULL)
    {
        printf("Error New_File!");
    }

    while (fgets(buffer, BUFF_LEN, fptr)) {
        list = (char**)malloc((sizeof(char*)));
        printf("%s", buffer);
        get_input(buffer, &list, &list_len);
        if (list)
        {
            if (has_macro(list_of_macros_names, list, name_list_len, &list_len))
            {
                printf("thats the macro");

                parse_the_macro(new_file, macro_commands, *macro_list_len, *name_list_len);
            }
        }
        put_input(new_file, list, list_len);
    }
    fclose(new_file);
    return 1;
}



int check_definitions()
{
	return 1;
}

int check_operations()
{
	return 1;
}
