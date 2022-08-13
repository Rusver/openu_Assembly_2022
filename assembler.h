#ifndef OPENU_ASSEMBLY_2022_ASSEMBLER_H
#define OPENU_ASSEMBLY_2022_ASSEMBLER_H
#include "pre_and_parcer.h"
#include <ctype.h>
#include "base_helper.h"
#define ADDRESS_START 100

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
void extern_handler(char* buffer);
void entry_handler(char* buffer);
int opcode_handler(char* buffer);
int put_word_singleLine(FILE* new_file, char* list, int list_len);
void assembly_print(FILE* fptr, int ic, int dc);
void test_base32();
int address_type(char* word);
int concatenate(int x, int y);
#endif /*OPENU_ASSEMBLY_2022_ASSEMBLER_H*/

