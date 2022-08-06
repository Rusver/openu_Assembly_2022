#include "files.h"
#include "parser.h"

void open_files(int argc, char *argv[])
{

	int i;
    FILE *fptr;
    char *file_name;
    char buff[BUFF_LEN];  /*TODO: create error if no file*/

	/*getcwd(buff, sizeof(buff));*/
	printf("YOU ARE IN OPEN_FILES");
	for (i = 1; i < argc; i++)
	{
		file_name = (char *)malloc(strlen(buff)+ 2 + strlen(argv[i]) + strlen(".txt") + 1);
		if (!file_name)
			printf("memory allocation failed");

		strncpy(file_name, buff, strlen(buff));
		strcat(file_name, "\\");
		strcat(file_name, argv[i]);
		strcat(file_name, ".txt");

		fptr = fopen("file.as", "r"); /*TODO: make it dynamic*/
		if (!fptr) /* If the wasn't found, or it isn't allowed for reading, the file pointer is NULL */
		{
			fprintf(stderr, "Couldn't open file %s\n", file_name);
		}


		/* Starts the first and second passes, and if they are finished successfully, writes the output files */
		if (first_read(fptr) && second_read())
			printf("write_output_files");
		/*write_output_files(argv[i]);*/


		fclose(fptr); /* Closes the file after reading and frees the file_name string for the next file name */
		file_name = NULL;
		free(file_name);
	}

}

int put_input(FILE* new_file, char** list, int list_len)
{
    int i=0;

    for(i =0; i < list_len; i++)
        fprintf(new_file, "%s ", list[i]);
    fprintf(new_file, "%c", '\n');

    return 1;
}

int parse_the_macro(FILE* new_file, char**** macro_commands, int macro_list_len, int name_list_len)
{
    int i=0,j=0, k=0;
    for(i = 0; i < name_list_len; i++)
    {
        for (j=0; j < macro_list_len; j++)
        {
            while (macro_commands[i][j][k])
            {
                fprintf(new_file, "%s", macro_commands[i][j][k]);
                if (macro_commands[i][j][k+1])
                {
                    fprintf(new_file, " ");
                }
                k++;
            }
            fprintf(new_file, "%c", '\n');
            k=0;
        }
    }



    return 1;
}
