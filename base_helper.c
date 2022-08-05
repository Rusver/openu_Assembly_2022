#include "base_helper.h"

char symbols[32]={'!','@','#','$','%','^','&','*','<','>',
                  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};


int binaryToDecimal(int bin) {

    int last_digit, decimal = 0, index = 1;
    int tempBin = bin;

    while (tempBin) {
        last_digit = tempBin % 10;
        tempBin /= 10;
        decimal += last_digit * index;
        index *= 2;
    }

    return decimal;
}

int decimalToBin(int decimal) {

    int divisionLeftover, bin = 0, index = 1;
    int tempDecimal = decimal;

    while (tempDecimal) {
        divisionLeftover = tempDecimal % 2;
        tempDecimal /= 2;
        bin += divisionLeftover * index;
        index *= 10;
    }

    return bin;
}

char binary_to_base32(int bin) {

    int decimal;
    decimal = binaryToDecimal(bin);
    return symbols[decimal];
}

int base32_to_binary(char c) {

    int index, symbolIndex, binary;

    for(index=0; index<32; index++) {
        if(c == symbols[index]) {
            symbolIndex = index;
            binary = decimalToBin(symbolIndex);
        }
    }

    return binary;
}


void printBin(int a)
{
    unsigned int msk = 1<<8*(sizeof(int)-1); /*size of long*/
    printf("\n");
    while (msk)
    {
        printf("%d",a&msk?1:0); /*check if the bit is 1 so print 1 else print 0*/
        msk>>=1;
    }
    printf("\n");
}

int op_code_parser(char* opCode)
{
    int opCodeIndex, binary = 0;

    for(opCodeIndex=0; opCodeIndex<16; opCodeIndex++)
        if(strcmp(&opCode[opCodeIndex],opCode) == 0) {
            binary = decimalToBin(opCodeIndex);
        }


    return binary;
}
