#ifndef OPENU_ASSEMBLY_2022_ASSEMBLER_H
#define OPENU_ASSEMBLY_2022_ASSEMBLER_H
#include "pre_and_parcer.h"
#include <ctype.h>

/**
 * This function will handle the all assembler encoding
 * @param fptr
 */
void assembler(FILE* fptr);

/**
 * This function is handling the data type
 * @param buffer
 * @return int - number of the digits
 */
int data_handler(char* buffer);
int string_handler(char* string);
int struct_handler(char* buffer);

#endif /*OPENU_ASSEMBLY_2022_ASSEMBLER_H*/

