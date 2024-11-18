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

int str_reverse(char** str) {
    if(str == NULL) return INVALID_PARAMETER;

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

    char* reversed_str = (char*) malloc(sizeof(char) * end + 1);

    char* p_revstr = reversed_str;
    while (end >= 0) {
        *p_revstr++ = (*str)[end--];
    }
    *p_revstr = '\0';
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
    if(str == NULL) return INVALID_PARAMETER;

    int len, result_code;
    if ((result_code = str_len(*str, &len)) != OK) return result_code;

    int dumb_counter = 0;
    for(char* p_str = *str; *p_str != '\0'; p_str++) {
        if (dumb_counter++ % 2 == 0) continue;
        *p_str = toupper(*p_str);
    }
    return OK;
}