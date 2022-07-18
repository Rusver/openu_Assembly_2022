

#include "parcer.h"

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

