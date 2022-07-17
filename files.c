#include "files.h"
#include "parcer.h"

void open_files(int argc, char *argv[])
{

	int i;
	FILE *fptr;
	char *file_name;
	char buff[BUFF_LEN];

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

		fptr = fopen("file.as", "r");
		if (!fptr) /* If the wasn't found, or it isn't allowed for reading, the file pointer is NULL */
		{
			fprintf(stderr, "Couldn't open file %s\n", file_name);
		}


		/* Starts the first and second passes, and if they are finished successfully, writes the output files */
		if (!first_read(fptr) && !second_read(fptr))
			printf("write_output_files");
		/*write_output_files(argv[i]);*/


		fclose(fptr); /* Closes the file after reading and frees the file_name string for the next file name */
		file_name = NULL;
		free(file_name);
	}

}
