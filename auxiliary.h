#pragma once
#include <string.h>
#include <ctype.h>

#define OK 0
#define ERR (-1)
#define INVALID_INPUT (-2)
#define INVALID_PARAMETER (-3)
#define MEMORY_ALLOCATION_ERROR (-4)

#define PRINT_ERROR_MESSAGE() printf("Error: unforeseen error. Restarting the program may help.")
#define PRINT_INVALID_INPUT_MESSAGE() printf("Error: invalid input. Please restart the program and pass proper input values.")
#define PRINT_INVALID_PARAMETER_MESSAGE() printf("Error: invalid parameter. Restarting the program may help.")
#define PRINT_MEMORY_ALLOCATION_ERROR() printf("Error: couldn't allocate memory. Restarting the program may help.")

int str_len(char* str, int* result);
int str_reverse(char** str);
int change_characters_case(char** str);
int shift_characters(char** str);
int random_concat(char** strings, int count, unsigned int seed, char** result);

int str_reverse(char** str) {
    if(str == NULL || *str == NULL) return INVALID_PARAMETER;

    int end;
    int result_code = str_len(*str, &end);
    if (end == 0) return INVALID_PARAMETER;

    switch(result_code) {
        case OK:
            end--;
            break;
        case INVALID_PARAMETER:
            return INVALID_PARAMETER;
        default:
            return result_code;
    }

    char* reversed_str = NULL;
    if ((reversed_str = (char*) malloc(sizeof(char) * end + 1)) == NULL) return MEMORY_ALLOCATION_ERROR;

    char* p_revstr = reversed_str;
    while (end >= 0) {
        *p_revstr++ = (*str)[end--];
    }
    *p_revstr = '\0';

    free(*str);
    *str = reversed_str;

    return OK;
}

int str_len(char* str, int* result) {
    if (str == NULL) return INVALID_PARAMETER;

    char* s_ptr = str;
    int len = 0;
    for (char* ptr = s_ptr; *ptr != '\0'; ptr++) len++;

    *result = len;
    return OK;
}

int change_characters_case(char** str) {
    if(str == NULL || *str == NULL) return INVALID_PARAMETER;

    int len, result_code;
    if ((result_code = str_len(*str, &len)) != OK) return result_code;

    int dumb_counter = 0;
    for(char* p_str = *str; *p_str != '\0'; p_str++) {
        if (dumb_counter++ % 2 == 0) continue;
        *p_str = toupper(*p_str);
    }
    return OK;
}

int shift_characters(char** str) {
    if (str == NULL || *str == NULL) return INVALID_PARAMETER;

    int len, result_code;
    if((result_code = str_len(*str, &len)) != OK) return result_code;
    if(len == 0) return INVALID_PARAMETER;

    char* result = NULL;
    if ((result = (char*) malloc(sizeof(char) * len + 1)) == NULL) return MEMORY_ALLOCATION_ERROR;

    char* p_result = result;
    char* p_str = *str;
    for(; *p_str != '\0'; p_str++) if (isdigit(*p_str)) *p_result++ = *p_str;

    for (p_str = *str; *p_str != '\0'; p_str++) if (isalpha(*p_str)) *p_result++ = *p_str;

    for (p_str = *str; *p_str != '\0'; p_str++) if(!isdigit(*p_str) && !isalpha(*p_str)) *p_result++ = *p_str;

    *p_result++ = '\0';
    *str = result;

    return OK;
}

int is_in_array(int* array, size_t size, int value);

int random_concat(char** strings, int count, unsigned int seed, char** result) {
    if(strings == NULL || count == 0) return INVALID_PARAMETER;

    if (*result != NULL) free(*result);
    srand(seed);

    int* checked = NULL;
    if((checked = (int*) malloc(sizeof(int) * count)) == NULL) return MEMORY_ALLOCATION_ERROR;
    int* p_checked = checked;

    char** p_strings = strings;
    char* new_string = NULL;
    if((new_string = (char*) malloc(sizeof(char) * BUFSIZ * count + 1)) == NULL) return MEMORY_ALLOCATION_ERROR;
    char* p_newstr = new_string;
    int i, random_index;
    for(i = 0; i < count; i++) {
        do {
            random_index = rand() % (count);
        } while(is_in_array(checked, count, random_index));
        *p_checked++ = random_index;

        char* current_str = p_strings[random_index];

        char* p_currstr = current_str;

        for(; *p_currstr != '\0'; p_currstr++) {
            *p_newstr++ = *p_currstr;
        }
    }
    *result = new_string;

    return OK;
}

int is_in_array(int* array, size_t size, int value) {
    int* p_array = array;

    for(int i = 0; i < size; i++) {
        if(*p_array++ == value) return 1;
    }
    return 0;
}