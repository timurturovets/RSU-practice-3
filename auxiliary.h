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
int is_in_array(int* array, size_t size, int value);

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



int is_in_array(int* array, size_t size, int value) {
    int* p_array = array;

    for(int i = 0; i < size; i++) {
        if(*p_array++ == value) return 1;
    }
    return 0;
}

// pozornaya funkciya sori
int integer_len(int num) {
    int c = 0;
    while(num != 0) {
        c++; num /= 10;
    }
    return c;
}

int ctod(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    else if (c >= 'A' && c <= 'Z') return 10 + (c - 'A');
    else return -1;
}

char dtoc(int digit) {
    if (digit >= 0 && digit <= 9) return '0' + digit;
    else if (digit >= 10 && digit <= 35) return 'A' + (digit - 10);
    else return -1;
}