
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parcer.h"

#define BUFF_LEN 256

/**
* @brief this function will open the file and handle the whole proceess - read, preProcess and etc..
*
* @param argc
* @param argv
*/
void open_files(int argc, char *argv[]);
void write_ob_file(FILE *fptr);
void write_ent_file();
void write_ext_file();
