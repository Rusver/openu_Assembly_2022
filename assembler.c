#include "assembler.h"
#include "hashTable.h"

void assembler(FILE* fptr)
{
    int ic = 0;
    int dc = 0;

    FILE* last_file;
    FILE* extern_file;
    FILE* intern_file;
    char buffer[BUFF_LEN];
    char** list = NULL;
    int list_len = 0;
    char res[BUFF_LEN];
    int binary_code = -1;
    int skip_flag = 0;

    last_file = fopen("ps.ob", "w");
    if (!last_file)
    {
        fprintf(stderr, "Couldn't open file %s\n", "ps.ob");
    }

    extern_file = fopen("ps.ext", "w");
    if (!fptr) /* If the wasn't found, or it isn't allowed for reading, the file pointer is NULL */
    {
        fprintf(stderr, "Couldn't open file %s\n", "ps.ext");
    }

    intern_file = fopen("ps.ent", "w");
    if (!fptr) /* If the wasn't found, or it isn't allowed for reading, the file pointer is NULL */
    {
        fprintf(stderr, "Couldn't open file %s\n", "ps.ent");
    }

    while (fgets(buffer, BUFF_LEN, fptr))
    {
        list = calloc(1, (sizeof(char *)));
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
            if(!strcmp(list[0], ".extern"))
            {
                file_handler(extern_file, buffer);
            }
            else if(!strcmp(list[0], ".entry"))
            {
                printf("ATTENTION! Entry Detected!");
                file_handler(intern_file, buffer);
            }
            else
            {
                skip_flag = 1;
                binary_code =  opcode_handler(buffer);
            }
        }
        binary_code = binaryToDecimal(binary_code);
        assembly_print(last_file ,ADDRESS_START+ic, binary_code);
        if (skip_flag)
            binary_code = address_analyze(last_file, buffer, &ic, &dc);


        ic++;

        free_list(list);
        free(list);
        memset(buffer,0, BUFF_LEN);
        binary_code = -1;
        skip_flag = 0;
    }
    printf("data counter: %d ", dc);

    printf("%s", decimal_to_mixedBase32(res,dc));
    fclose(last_file);
    fclose(fptr);
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
                printf("Error! the .data is not right\n");
        }
        else {
            cspn = strcspn(token, "\n");
            digit_len = strlen(token);
            if (token[0] == '\n')
            {
                printf("ERROR! there is a comma in the last digit\n");
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
                printf("Error! the .data is not right after the first comma\n");
        }

        digit_num++;
        token = strtok(NULL, ",");
    }

    free(line_by_comma);
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
    free(line_by_comma);
    free(line_by_sign);
    return dc;
}

char* getOPC (char* buffer)
{
    int i = 0;
    char* copy = malloc(strlen(buffer+1));
    char *p;
    char *array[3];
    strcpy(copy,buffer);

     p = strtok (copy, " ");

    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, " ");
    }

    return array[1];
}

void file_handler(FILE* fptr, char* buffer)
{
    char res[100];
    char* base32;
    char* opc = getOPC(buffer);

    struct DataItem* item = search_by_string(opc);
    if (item)
    {
        base32 = decimal_to_mixedBase32(res,item->key);

        put_word_singleLine(fptr, opc, strlen(opc));
        put_word_singleLine(fptr,"\t", 1);
        put_word(fptr,base32, strlen(base32));


    }
}


void entry_handler(char* buffer)
{
    FILE* fptr;
    fptr = fopen("ps.ent", "w");
    if (!fptr) /* If the wasn't found, or it isn't allowed for reading, the file pointer is NULL */
    {
        fprintf(stderr, "Couldn't open file %s\n", "ps.ent");
    }

    put_word(fptr, &buffer[1], strlen(&buffer[1]));

    fclose(fptr);

}

long opcode_handler(char* buffer)
{
    char* token;
    char* line_by_space;
    int opcode = -1;
    int opcode_flag = 0;
    char* split_by_comma;
    int ad_type = -1;
    int are_type = 0;
    struct DataItem* item;
    char* str = NULL;
    char bstr[OPCODE_LEN] = {0};
    int loop_idx =0;
    int free_comma_flag =0;
    int free_flag = 0;
    long address = 0;

    line_by_space = malloc(strlen(buffer));
    strcpy(line_by_space, buffer);


    token = strtok(line_by_space, " ");
    /* opcode_handler*/

    while (token != NULL) {
        if (opcode_flag == 0)
        {
            /* check if it is an opcode*/
            opcode = op_code_parser(token);
            if (opcode)
            {
                opcode = opcode - 1;
                opcode = binaryToDecimal(opcode);
                opcode_flag = 1;
                string_code_helper(bstr, opcode, 4);
                loop_idx = 0;
            }
        }
        else
        {
            str = malloc(sizeof(token));
            strcpy(str, token);
             /*deep copy do not break th split_by_space */
            if (str[0] == ',')
            {
                free_comma_flag = 1;
                split_by_comma = malloc(strlen(str));
                strcpy(split_by_comma, str);
                free(str);
                free_flag = 1;
                str = strtok(split_by_comma, ",");
            }
            if (str[0] == '\t')
                memmove(str, str + 1, strlen(str));
            if (str[0] == ' ')
                memmove(str, str + 1, strlen(str));
            ad_type = address_type(str);
            if (ad_type == 1 || ad_type == 2)
            {
                str[strcspn(str, ".")] = '\0'; /*check if right place*/
                item = search_by_string(str); /*check the TAGS*/
                if (item)
                    are_type = item->type; /*if 1 is extern if 0 not*/
            }
            if(ad_type != -1)
            {
                if(loop_idx == 1)
                {
                    string_code_helper(bstr, ad_type, 2);
                }
                if(loop_idx == 2)
                {
                    string_code_helper(bstr, ad_type, 2);
                }
            }
            if (free_flag == 0) {
                free(str);
                str = NULL;
            }
        }

        token = strtok(NULL, " ");
        loop_idx++;
    }
    string_code_helper(bstr, are_type, 2);
    /*check which type of register it is*/
    free(line_by_space);
    if(free_comma_flag)
        free(split_by_comma);

    bstr[10] = '\0';
    address = atoi(bstr);
    if (address < 0)
            address = 0;
    return address;
}

void string_code_helper(char* str, int type, int bits) {
        int code = 0;
        int digit_len = 0;
        int i = 0;
        char *temp;

        code = decimalToBin(type);
        digit_len = floor(log10(abs(code))) + 1;
        if (code == 0)
                digit_len = 0;
        for (i = 0; i < bits - digit_len; i++)
                strcat(str, "0");
        if (code != 0)
        {
        temp = int_to_string(code);
        strcat(str, temp);
        free(temp);
        }

}

int address_type(char* word)
{
    int address_type = -1;
    int cspn;
    int word_len;

    if(word[0] == 'r') /* if register*/
    {
        address_type = 3;
    }
    else if(word[0] == '#') /* if number */
    {
        if (word[1] == '-' || word[1] == '+')
        {
            if (isdigit((word[2])))
            {
                address_type = 0;
            }
            else printf("Error! the .data is not right after the first comma\n");
        }
        else if (isdigit((word[1])))
        {
            address_type = 0;
        }
        else printf("Error OpCodeHandler! this is not digit\n");
    }
    else
    {
        cspn = strcspn(word, ".");
        word_len = strlen(word);
        if (search_by_string(word))
        {
            return 1;
        }
        else if (cspn != 0 && cspn < word_len)
        {
            return 2;
        }
    }

    return address_type;
}


int concatenate(int x, int y) {
    int pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
}

void assembly_print(FILE* fptr, int ic, int dc)
{
        int free_flag = 0;
    char ic_base32_res[BUFF_LEN];
    char dc_base32_res[BUFF_LEN];

    char *ic_base32 = NULL;
    char *dc_base32 = NULL;

    ic_base32 = decimal_to_mixedBase32(ic_base32_res,ic);
    if (dc <= 32)
    {
            dc_base32 = base32_for_rookies(dc);
            free_flag = 1;
    }


    else
        dc_base32 = decimal_to_mixedBase32(dc_base32_res,dc);

    put_word_singleLine(fptr,ic_base32, strlen(ic_base32));
    put_word_singleLine(fptr,"\t", 1);
    put_word(fptr,dc_base32, strlen(dc_base32));
    if (free_flag)
            free(dc_base32);
}

int put_word_singleLine(FILE* new_file, char* list, int list_len)
{
    fprintf(new_file, "%s ", list);

    return 1;
}

int address_analyze(FILE* last_file ,char* buffer, int* ic, int* dc)
{
    char* line_by_space;
    char* token;
    int opcode_flag = 0;
    int opcode = 0;
    char** list = 0;
    struct DataItem* item;
    int address = 0;
    char* str;
    char* temp;
    int free_comma_flag = 0;
    char* split_by_comma;
    int ad_type = -1;
    int num = 0;
    char register_code[10] = {0};
    int loopIndex = 1;
    char temp_str[4] = {0};
    int are_type = 0;
    int reg_flag = 0;
    int stop_flag = 0;
    int cspn_flag = 0;
    int i = 0;
    char** temp_pointer;
    int label_counter = 0;
    int cspn_idx = -1;
    char* item_pointer;

    list = malloc(sizeof(char*));
        line_by_space = calloc(strlen(buffer), sizeof(char));
    strcpy(line_by_space, buffer);


    token = strtok(line_by_space, " ");

    while (token != NULL) {
        list[i] = calloc(sizeof(strlen(token)), sizeof(char));
        strcpy(list[i], token);
        i++;
        temp_pointer = realloc(list, sizeof(char*)*(i+1));
        if(temp_pointer != NULL)
        {
            list = temp_pointer;
        }
        token = strtok(NULL, " ");
    }
    list[i] = NULL;

    if (opcode_flag == 0) {
        /* check if it is an opcode*/
        opcode = op_code_parser(list[0]);
        if(!opcode)
        {
            label_counter++;
            opcode = op_code_parser(list[1]);
        }
        if (opcode) {
            opcode = opcode - 1;
            opcode_flag = 1;

            while(stop_flag == 0 && loopIndex != 2) {

                str = list[1 + label_counter];

                if (str[0] == ',') {
                    free_comma_flag = 1;
                    split_by_comma = malloc(strlen(str));
                    strcpy(split_by_comma, str);
                    free(str);
                    str = strtok(split_by_comma, ",");
                }
                if (str[0] == '\t')
                    memmove(str, str + 1, strlen(str));
                if (str[0] == ' ')
                    memmove(str, str + 1, strlen(str));
                ad_type = address_type(str);
                if (ad_type == 0) {

                    if (str[1] == '+') {
                        num = atoi(&str[2]);
                    } else if (str[1] == '-') {
                        num = -atoi(&str[2]);
                        num = binaryToDecimal(two_complement(num));
                    } else
                        num = atoi(&str[1]);

                    string_code_helper(register_code, num, 8);
                }
                else if (ad_type == 1 || ad_type == 2)
                {
                    cspn_idx = strcspn(str, ".");
                    temp = malloc(strlen(str - cspn_idx));
                    strcpy(temp, str + (cspn_idx+1)); /*get the number */
                    if (cspn_idx)
                    {
                        cspn_flag = 1;
                    }

                    str[cspn_idx] = 0;
                    item = search_by_string(str); /*check the TAGS*/
                    if (item)
                    {
                        are_type = item->type;
                        address = item->key;
                        /*print address*/
                        assembly_print(last_file, ADDRESS_START+(*ic), address);
                        (*ic)++;
                    }

                    if(cspn_flag)
                    {

                        item_pointer = item->list[1 + atoi(&temp[0])];
                        if(item_pointer[0] == '\"')
                            string_printer(item_pointer, last_file, ic);
                        else
                        {
                            if (item_pointer[0] == '+') {
                                num = atoi(&item_pointer[1]);
                            }
                            else if (item_pointer[0] == '-') {
                                num = -atoi(&item_pointer[1]);
                                num = binaryToDecimal(two_complement(num));
                            } else
                                num = atoi(&item_pointer[0]);

                            assembly_print(last_file, ADDRESS_START+(*ic), num);
                            (*ic)++;
                        }

                    }



                        free(temp);
                } else if (ad_type == 3) {

                    num = atoi(&str[1]);
                    num = decimalToBin(num);
                    string_code_helper(temp_str, num, 4);

                    if (loopIndex == 2 && reg_flag == 0) {
                        string_code_helper(register_code, 0, 4);
                        strcat(register_code, temp_str);
                    } else {
                        string_code_helper(register_code, num, 4);
                        string_code_helper(register_code, 0, 4);
                    }

                    reg_flag = 1;
                } else
                    printf("Error with address_type in address_analyze function");

                if (opcode > 6) /* if only one character */
                {
                    stop_flag = 1;
                }

                loopIndex++;
            }
        }
    }
    string_code_helper(register_code, are_type, 2);

    free(temp_pointer);
    free_list(list);
    free(list);
    free(line_by_space);
    if (free_comma_flag)
        free(split_by_comma);

    return atoi(register_code);
}

void string_printer(char* str, FILE* last_file, int* ic)
{
    int i = 1;
    while (str[i] != '\"' && str[i] != '\0')
    {
        assembly_print(last_file, ADDRESS_START + (*ic), (int)str[i]);
        (*ic)++;
        i++;
    }
}
