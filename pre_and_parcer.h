#include "files.h"

/**
 * handles the macro commands
 * @param fptr - the file we read from
 * @param macro_list_len - len of the commannds list
 * @param macro_commands - in the end we get set of commands by [name][line][command]
 * @return list_of_macros_names
 */
char** macro_handler(FILE* fptr, int * macro_list_len, char**** macro_commands);
int check_definitions();
int check_operations();

/**
 * This function is read the file for the first time and parses the macros,
 * we should get expanded file.as with expanded macros
 * @param fptr
 * @return
 */
int first_read(FILE *fptr);

/**
 *
 * @param fptr
 * @return
 */
int second_read(FILE *fptr);

/**
 * boolean function that check if we have "macro" in the list
 * @param list
 * @return 1 if its macro or 0 if its not
 * there is no binary in c90
 */
int is_macro(char** list);

/**
 * boolean function that check if we have "endmacro" in the list
 * @param list
 * @param list_len
 * @return 1 if there is "endmacro" or 0 if there is no "endmacro"
 */
int is_end_of_macro(char** list, int list_len);

/**
 * get the list line and separates its by " " (space) to a list
 * @param line - the whole line string
 * @param list - the seperated line
 * @param idx - index of the list
 */
void get_input(char* line, char** list, int* idx);
