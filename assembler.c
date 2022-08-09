#include "assembler.h"

void assembler(FILE* fptr)
{
    int ic = 0;
    int dc = 0;

    char buffer[BUFF_LEN];
    char** list = NULL;
    int list_len = 0;


    while (fgets(buffer, BUFF_LEN, fptr))
    {
        list = (char **) malloc((sizeof(char *)));
        printf("%s", buffer);
        get_input(buffer, &list, &list_len);
        if (list) {
            if (!strcmp(list[1], ".data"))
            {
                dc += data_handler(buffer);
            }
            else if(!strcmp(list[1], ".string"))
            {
                dc += string_handler(list[2]);
            }
            else if(!strcmp(list[1], ".struct"))
            {
                dc += struct_handler(buffer);
            }
            else if(!strcmp(list[1], ".extern"))
            {

            }
            else if(!strcmp(list[1], ".entry"))
            {

            }
            else
            {
                /* opcode handler */
            }
        }
        ic++;
    }
}

int data_handler(char* buffer)
{
    char* token;
    char* line_by_comma;
    int first_num_flag = 0;
    int cspn = 0;
    int digit_len = 0;
    int digit_num = 0;

    line_by_comma = malloc(strlen(buffer));

    strcpy(line_by_comma, buffer);


    token = strtok(line_by_comma, ",");


    while (token != NULL)
    {
        if (token[0] == '\t')
            memmove(token, token + 1, strlen(token));

        if (token[0] == ' ')
            memmove(token, token + 1, strlen(token));

        if(first_num_flag == 0) {
            if (isdigit((token[strlen(token) - 1])))
                first_num_flag = 1;
            else
                printf("Error! the .data is not right");
        }
        else {
            cspn = strcspn(token, "\n");
            digit_len = strlen(token);
            if (token[0] == '\n')
            {
                printf("ERROR! there is a comma in the last digit");
                digit_num--;
            }
            if (cspn != 0 && cspn < digit_len)
            {
                token[strcspn(token, "\n")] = '\0';
            }
            if (token[0] == '-' || token[0] == '+')
            {
                memmove(token, token+1, 1);
                token[1] = '\0';
            }
            if(!isdigit((token[0])))
                printf("Error! the .data is not right after the first comma");
        }

        digit_num++;
        token = strtok(NULL, ",");
    }
    return digit_num - 1;
}

int string_handler(char* string)
{
    /*every character to byte*/

    return strlen(string);
}

int struct_handler(char* buffer)
{
    char* line_by_comma;
    char* line_by_sign;
    char* token;
    int token_len = 0;
    int first_num_flag = 0;
    int string_flag = 0;
    int dc = 0;

    line_by_comma = malloc(strlen(buffer));
    line_by_sign = malloc(strlen(buffer));

    strcpy(line_by_comma, buffer);
    strcpy(line_by_sign, buffer);

    token = strtok(line_by_comma, ",");

    while (token != NULL)
    {
        token_len = strlen(token);
        if (token[0] == '\t')
            memmove(token, token + 1, token_len);

        if (token[0] == ' ')
            memmove(token, token + 1, token_len);

        if(first_num_flag == 0) {
            if (isdigit((token[token_len - 1])))
            {
                first_num_flag = 1;
                dc++;
            }

        }
        if(token[token_len - 1] == '\"' && string_flag == 0)
        {
            token = strtok(line_by_sign, "\"");
            string_flag = 1;
        }
        else if(string_flag == 1)
        {
            token[strcspn(token, "\"")] = '\0';
            dc += strlen(token)-1;
        }
        token = strtok(NULL, ",");
    }
    return dc;
}

