#include "preprocessor.h"

char* macro_handler(FILE* fptr, int * macro_list_len, char**** macro_commands)
{
	char buffer[BUFF_LEN];
	char** list = NULL;
	char** list_of_macros_names = NULL;
	int macro_counter = 0;
	char* macro_name;
	int list_len = 0;
	int name_list_len = 0;
	int macro_len = 0;
	int line_count = 0;
	int initizilied_flag = 0;
	
	list_of_macros_names = (char**)malloc(sizeof(char*));

	while (fgets(buffer, BUFF_LEN, fptr))
	{
		list = (char**)malloc((sizeof(char*)));
		printf("%s", buffer);
		get_input(buffer, list, &list_len);
		if (list && (is_macro(list)) == 1 || macro_counter)
		{
			if (is_end_of_macro(list, list_len))
			{
				macro_len = macro_counter;
				macro_counter = -1;
			}
			else if (macro_counter == 0)
			{

				list_of_macros_names[name_list_len] = (char*)malloc(strlen(list[1]));
				macro_name = list_of_macros_names[name_list_len];
				strncpy(macro_name, list[1], strlen(list[1]) + 1);
				(macro_name)[strcspn(macro_name, "\n")] = 0;  /*delete \n in the macro name*/
				name_list_len++;
				initizilied_flag = 0;
			}
			else
			{
				if (name_list_len > 1 && initizilied_flag == 0)
				{
					macro_commands[name_list_len - 1] = (char*)malloc(sizeof(char*));
					initizilied_flag = 1;
				}
					
				macro_commands[name_list_len - 1][macro_counter - 1] = list;
			}
			macro_counter += 1;


		}
		/*free_list(list, list_len);*/
	}
	
	return list_of_macros_names;
}



int check_definitions()
{
	return 1;
}

int check_operations()
{
	return 1;
}
