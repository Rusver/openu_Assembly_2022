#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define BUFF_LEN 256

/**
* @brief this function will open the file and handle the whole proceess - read, preProcess and etc..
* @param argc
* @param argv
*/
void open_files(int argc, char *argv[]);
/**
 * a function that write the list to the file
 * @param new_file
 * @param list
 * @param list_len
 * @return 1 for success
 */
int put_input(FILE* new_file, char** list, int list_len);
/**
 * a function that write line to the file
 * @param new_file
 * @param list
 * @param list_len
 * @return 1 for success
 */
int put_word(FILE* new_file, char* list, int list_len);
/**
 * a function that will change the macro to the set of commands
 * @return 1 for success
 */
int parse_the_macro(FILE* new_file, char**** macro_commands, int macro_list_len, int name_list_len);



void write_ob_file(FILE *fptr);
void write_ent_file();
void write_ext_file();
