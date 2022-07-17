#include <stdio.h>

#define BUFF_LEN 256

int first_read(FILE *fptr);

int second_read(FILE *fptr);

int is_macro(char** list);

int is_end_of_macro(char** list);

void get_input(char* line, char** list);