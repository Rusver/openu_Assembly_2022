#include "main.h"
#include "base_helper.h"

int main(int argc, char *argv[]) {
    open_files(argc, argv);
    /*test_base32();*/





    return 0;
}

void test_base32()
{
    char res[100];
    int i = 0;
    char *x;
    for (i = 100; i < 257; i++)
    {
        x = decimal_to_mixedBase32(res,i);
        printf("%d\t", i);
        printf("%s\n", x);
    }
}


void test_binary()
{
    printf("~~~~~binaryTODecimal~~~~~\n");
    printf("%d\n", binaryToDecimal(1));
    printf("%d\n", binaryToDecimal(10));
    printf("%d\n", binaryToDecimal(11));
    printf("%d\n", binaryToDecimal(100));
    printf("%d\n", binaryToDecimal(1010101));

    printf("~~~~~decimalToBin~~~~~\n");
    printf("%d\n", decimalToBin(85));
    printf("%d\n", decimalToBin(0));
    printf("%d\n", decimalToBin(1));
    printf("%d\n", decimalToBin(2));
    printf("%d\n", decimalToBin(3));
    printf("%d\n", decimalToBin(4));

    printf("~~~~~binary_to_base32~~~~~\n");
    printf("%c\n", binary_to_base32(0));
    printf("%c\n", binary_to_base32(10));
    printf("%c\n", binary_to_base32(11));
    printf("%c\n", binary_to_base32(100));
    printf("%c\n", binary_to_base32(1101));
    printf("~~~~~base32_to_binary~~~~~\n");
    printf("%d\n", base32_to_binary('!'));
    printf("%d\n", base32_to_binary('@'));
    printf("%d\n", base32_to_binary('#'));
    printf("%d\n", base32_to_binary('$'));
    printf("%d\n", base32_to_binary('%'));
    printf("%d\n", base32_to_binary('d'));
}


