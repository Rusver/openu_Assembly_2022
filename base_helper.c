#include "base_helper.h"

char symbols[32]={'!','@','#','$','%','^','&','*','<','>',
                  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};

char symshort[10] = {'!','@','#','$','%','^','&','*','<','>'};

char *opCodes[16] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","get","prn","jsr","rts","hlt"};



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
        if(strcmp(opCodes[opCodeIndex],opCode) == 0) {
            binary = decimalToBin(opCodeIndex);
            binary += 1; /*for the return*/
        }


    return binary;
}

char* parseToBaseSymbols32(char* rawBase32)
{
    char* base32 = rawBase32;

    base32[0] = binary_to_base32(rawBase32[0] - '0');
    if(isdigit(base32[1])) base32[1] = binary_to_base32(rawBase32[1] - '0');

    return base32;
}

char parseToBase32(int num)
{
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'a');
}

void reverse_string(char *str)
{
    int len = strlen(str);
    int i;
    for (i = 0; i < len/2; i++)
    {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

char* decimal_to_mixedBase32(char res[], int decimal)
{
    int index = 0;

    while (decimal > 0)
    {
        res[index++] = parseToBase32(decimal % 32);
        decimal /= 32;
    }
    res[index] = '\0';

    reverse_string(res);

    return parseToBaseSymbols32(res);
}


char* base32_for_rookies(int x)
{
    int r_x;
    int l_x;
    char* ch = malloc(3);
    char* str;
    int idx = -1;

    if (x < 10)
    {
        ch[0] = '0';
        str = int_to_string(x);
        ch[1] = str[0];

        idx = ch[0] - '0';
        ch[0] = symbols[idx];
        idx = ch[1] - '0';
        ch[1] = symbols[idx];
        ch[2] = '\0';
        free(str);
    }
    else
    {
        r_x = x % 10;
        l_x = x / 10;
        ch[0] = symbols[l_x];
        ch[1] = symbols[r_x];
        ch[2] = '\0';
    }
    return ch;
}


char* int_to_string(int x)
{
    int length = 0;
    char *str = malloc(1);
    if (x != 0)
    {
        length = floor(log10(abs(x))) + 1;
        free(str);
        str = malloc(length + 1);
        itoa(x, str);
    }
    else
        str[0] = '0';

    return str;
}

int two_complement(int decimal)
{
    int mask;
    char bin[9];
    int i =0;

    for (i = 0; i < 8; i++) {
        mask = 1u << (8 - 1 - i);
        bin[i] = (decimal & mask) ? '1' : '0';
    }
    bin[8] = '\0';

    return atoi(bin);
}

void itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0)  /* record sign*/
        n = -n;         /* make n positive*/
    i = 0;
    do {                /* generate digits in reverse order*/
        s[i++] = n % 10 + '0'; /* get next digit*/
    } while ((n /= 10) > 0);  /* delete it*/
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int c, i, j;

    for (i=0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


