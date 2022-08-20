#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/**
 * int function that convert operation code value into binary value
 * @param opCode - operation code to convert
 * @return binary value
 */
int op_code_parser(char* c);
/**
 * int function that convert binary value into decimal value
 * @param bin - binary value to convert
 * @return decimal value
 */
int binaryToDecimal(int bin);
/**
 * int function that convert decimal value into binary value
 * @param decimal - decimal value to convert
 * @return binary value
 */
int decimalToBin(int decimal);
/**
 * char function that convert single binary value into single base32 value
 * @param bin - binary value to convert
 * @return single base32 value
 */
char binary_to_base32(int bin);
/**
 * int function that convert single base32 value into single binary value
 * @param c - base32 value to convert
 * @return single binary value
 */

int base32_to_binary(char c);
/**
 * char list function that converts decimal number into special base32 value
 * @param rawBase32 - lchar ist to return
 * @param decimal - decimal value to convert
 * @return char list value
 */
char* decimal_to_mixedBase32(char res[], int decimal);
/**
 * This Function is converting a string to a reverse form
 * @param *str - string that will be reversed
 */
void reverse_string(char *str);
/**
 * char function that parses single decimal value into raw base32
 * @param num - single decimal to parse
 * @return single char value
 */
char parseToBase32(int num);
/**
 * char list function that parses raw base32 into base32 special symbols
 * @param rawBase32 - raw base32 to parse
 * @return char list value
 */
char* parseToBaseSymbols32(char* rawBase32);
/**
 * This Function is printing the bits in the variable
 * @param a - integer that will be converted
 */
void printBin(int a);


/**
 * char* function that converts int to string with allocation
 * @param x - number to convert
 * @return 1 for success
 */
char* int_to_string(int x);

/**
 * this function handles the integers that are smaller then 32
 * example 15 - @^
 * example 01 - !@
 * @param x
 * @return
 */
char* base32_for_rookies(int x);

/**
 * switching to the two's complement binary num
 * @param num
 * @return
 */
int two_complement(int decimal);
