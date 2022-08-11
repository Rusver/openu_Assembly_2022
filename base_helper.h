#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int op_code_parser(char* c);
int binaryToDecimal(int bin);
int decimalToBin(int decimal);
char binary_to_base32(int bin);
int base32_to_binary(char c);
char* decimal_to_mixedBase32(char res[], int decimal);
void reverse_string(char *str);
char parseToBase32(int num);
char* parseToBaseSymbols32(char* rawBase32);
void free_list(char** list);
void free_list_of_pointer(char*** list);


/**
 * This Function is printing the bits in the variable
 * @param a - integer that will be converted
 */
void printBin(int a);


