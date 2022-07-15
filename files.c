//ruslan

#include "files.h"

void open_files(int argc, char *argv[])
{
    int i;
    FILE *fptr;
    char *file_name;
    for (i=0; i < argc; i++)
    {   
        file_name = (char *)malloc(strlen(argv[i]) + strlen(".as"));
        if(!file_name)
            print_error("memory allocation failed");
        strcpy(file_name, argv[i]);
        strcat(file_name,".as");

        fptr = fopen(argv[i], "r");
        if(!fptr) /* If the wasn't found, or it isn't allowed for reading, the file pointer is NULL */
        {
            fprintf(stderr, "Couldn't open file %s\n", file_name);
        }


        /* Starts the first and second passes, and if they are finished successfully, writes the output files */
        if(!first_read(fptr) && !second_read(fptr))
            write_output_files(argv[i]);

        fclose(fptr); /* Closes the file after reading and frees the file_name string for the next file name */
        free(file_name);
    }

}