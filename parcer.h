
#include "files.h"


int first_read(FILE *fptr);

int second_read(FILE *fptr);

int is_macro(char** list);

int is_end_of_macro(char** list, int list_len);

void get_input(char* line, char** list, int* idx);


