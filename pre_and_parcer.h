#include "files.h"
#include "hashTable.h"
#include "assembler.h"

#define DECIMAL_ADDRESS 100


/**
 * handles the macro commands
 * @param fptr - the file we read from
 * @param name_list_len - len of the commannds list
 * @param macro_commands - in the end we get set of commands by [name][line][command]
 * @return list_of_macros_names
 */
char** macro_handler(FILE* fptr, int * name_list_len, char***** macro_commands, int* macro_list_len);
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
int second_read();

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
void get_input(char* line, char*** list, int* idx);

/**
 * int function will read the file and expand the macros - in a new file.
 * @param list_of_macros_names
 * @param macro_commands
 * @param name_list_len
 * @param macro_list_len
 * @return returns 1 for success write of the file
 */
int write_expanded_file(FILE *fptr, char** list_of_macros_names, char**** macro_commands, int* name_list_len, int* macro_list_len);

/**
 * int function the checks if there is a macro
 * @param list_of_macros_names
 * @param list
 * @param name_list_len
 * @param list_len
 * @return returns 1 if macro found
 */
int has_macro(char** list_of_macros_names, char** list, int* name_list_len, int* list_len);

/**
 * void function that does a deep copy of the command list
 * @param macro_commands
 * @param name_list_len
 * @param macro_list_len
 * @param list_len
 */
void deep_copy_command_list(char**** macro_commands, int name_list_len, int macro_list_len, char** list, int list_len);

/**
 * int function the checks if there is a macro
 * @param list
 * @return returns 1 if label and 0 if not
 */
int is_label(char* list);

/**
 * void function that frees the list (null)
 * @param list
 */
void free_list(char** list);

/**
 * This function is handeling the table for the macros of the .as file
 * @param fptr
 * @return
 */
int label_handler(FILE* fptr);

/**
 * void function that frees the deep list (null)
 * @param list
 * @param macro_list_len
 * @param name_list_len
 */
void free_arr_of_commands(char**** list, int macro_list_len, int name_list_len);

/**
 * int function the checks if there is string in a list of strings
 * @param word
 * @param list
 * @return returns 1 if label and 0 if not
 */
int is_in_ext_list(char* word, char** list);

/**
 * void function that realocates values to another list
 * @param list
 * @param word
 * @param idx
 */
void realloc_helper(char*** list, char* word, int idx);
