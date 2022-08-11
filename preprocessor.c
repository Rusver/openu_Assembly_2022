#include "pre_and_parcer.h"


char** macro_handler(FILE* fptr, int* name_list_len, char***** macro_commands, int* macro_list_len) /* return macro_counter */
{
	char buffer[BUFF_LEN];
    char**** mc_list = *macro_commands; /* Make things easier by avoiding one * within the function.*/
	char** list = NULL;
	char** list_of_macros_names = NULL;
	char* macro_name;
	int list_len = 0;
    int flag_to_stop = 0;
    char**** temp;

	/*int line_count = 0;*/
	int initizilied_flag = 0;
	
	list_of_macros_names = (char**)malloc(sizeof(char*));

	while (fgets(buffer, BUFF_LEN, fptr))

	{
		list = malloc((sizeof(char*)));
		printf("%s", buffer);
		get_input(buffer, &list, &list_len);  /*by line*/
		if ((list && (is_macro(list)) == 1) || flag_to_stop)
		{
			if (is_end_of_macro(list, list_len))
            {
                flag_to_stop = 0;
			}
			else if (*name_list_len == 0)
			{

				list_of_macros_names[*name_list_len] = (char*)malloc(strlen(list[1]));
				macro_name = list_of_macros_names[*name_list_len]; /*TODO: CHECK REMOVING THIS */
				strncpy(macro_name, list[1], strlen(list[1]) + 1);
				(macro_name)[strcspn(macro_name, "\n")] = 0;  /*delete \n in the macro name*/
                (*name_list_len)++;
                flag_to_stop =1;
				initizilied_flag = 0;
			}
			else
			{
				if (*name_list_len >= 1 && initizilied_flag == 0)
				{
					temp = realloc(*mc_list, sizeof(char*) * (*name_list_len + 1));
                    if (temp != NULL)
                        mc_list = temp;
					initizilied_flag = 1;
				}

                deep_copy_command_list(mc_list, *name_list_len, *macro_list_len, list, list_len);
                /*macro_commands[*name_list_len - 1][*macro_list_len - 1][list_len] = NULL;*/
                if (flag_to_stop != 0)
                    (*macro_list_len)++;
            }

		}
        *macro_commands = mc_list;
        free_list(list);
        free(list);
	}

	return list_of_macros_names;
}

void deep_copy_command_list(char**** mc_list, int name_list_len, int macro_list_len, char** list, int list_len)
{
    int i =0;
    char** temp;

    mc_list[name_list_len - 1][macro_list_len] = malloc(sizeof(char*));

    for (i =0; i < list_len; i++)
    {
        mc_list[name_list_len - 1][macro_list_len][i] = malloc(strlen(list[i])+1);
        strcpy(mc_list[name_list_len - 1][macro_list_len][i], list[i]);

        temp = realloc(mc_list[name_list_len - 1][macro_list_len], sizeof(char*) * ((i+1) + 1));
        if (temp != NULL)
            mc_list[name_list_len - 1][macro_list_len] = temp;
    }
    mc_list[name_list_len - 1][macro_list_len][i] = NULL;
}

int write_expanded_file(FILE *fptr, char** list_of_macros_names, char**** macro_commands, int* name_list_len, int* macro_list_len)
{


    char buffer[BUFF_LEN];
    char** list = NULL;
    int list_len = 0;
    FILE* new_file = NULL;
    int flag_to_stop = 0;

    new_file = fopen("extended.as", "w");
    if(new_file == NULL)
    {
        printf("Error New_File!");
    }

    while (fgets(buffer, BUFF_LEN, fptr)) {
        list = (char**)malloc((sizeof(char*)));
        /*printf("%s", buffer);*/
        get_input(buffer, &list, &list_len);
        if (list)
        {
            /* if is macro then turn the flag and start record the commands */
            if (is_macro(list) == 1 || flag_to_stop)
            {
                flag_to_stop = 1;
                if (is_end_of_macro(list, list_len)) {
                    flag_to_stop = 0;
                }
            }
            else if (has_macro(list_of_macros_names, list, name_list_len, &list_len))
            {
                printf("that׳s the macro");

                parse_the_macro(new_file, macro_commands, *macro_list_len, *name_list_len);
            }
            else
            {
                put_input(new_file, list, list_len);
            }
        }
    }
    fclose(new_file);
    return 1;
}

int label_handler(FILE* fptr)
{
    char buffer[BUFF_LEN];
    char** list = NULL;
    int list_len = 0;
    int lineIndex = 0;

    while (fgets(buffer, BUFF_LEN, fptr))
    {
        list = (char **) malloc((sizeof(char *)));
        printf("%s", buffer);
        get_input(buffer, &list, &list_len);
        if (list) {

            if (is_label(list[0]))
            {
                list[0][strcspn(list[0], ":")] = '\0';
                insert(list[0], DECIMAL_ADDRESS + lineIndex);
            }
        }
        lineIndex++;
        free(list);
    }
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
