#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_LEN 256
char *opCodes[16] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","get","prn","jsr","rts","hlt"};
enum op_num{MOV, CMP, ADD, SUB, NOT, CLR, LEA, INC,
    DEC, JMP, BNE, GET, PRN, JSR, RTS, HLT}; /* Matching the operations in the assembly language to numbers */
enum def_num{DATA, STRING, EXTERN, ENTRY, CODE}; /* Matching the definitions in the assembly language to numbers */
enum registers{r0,r1,r2 ,r3,r4,r5,r6,r7};

enum are{A, R, E}; /* Creating constants for the ARE section in a machine code word */
enum addressing_num{IMMEDIATE, DIRECT, INDIRECT_ADDRESSING, DIRECT_REGISTER}; /* Numbers of addressing methods,
                                                                               represented by their name */



void test_binary();
