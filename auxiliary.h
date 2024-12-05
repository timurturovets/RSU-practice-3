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
int integer_len(int num);
int ctod(char c);
char dtoc(int digit);
int get_fibonacci_seq(int ** const result, int * const result_count, int const number);
int get_zeckendorf_representation(char ** const result, unsigned int const number);


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

int get_fibonacci_seq(int ** const result, int * const result_count, int const number) {
    if (result == NULL || number < 2) return INVALID_PARAMETER;

    if (*result != NULL) free(*result);
    if ((*result = (int*) malloc(number * sizeof(int))) == NULL) return MEMORY_ALLOCATION_ERROR;

    int prev, mega_prev, * p_res = *result;
    *p_res++ = 0;
    *p_res++ = 1;

    *result_count = 2;
    while(1) {

        prev = *--p_res;
        mega_prev = *--p_res;
        if (prev + mega_prev > number) break;
        p_res++; p_res++;

        *p_res++ = prev + mega_prev;
        (*result_count)++;
    }
    return OK;
}

int get_zeckendorf_representation(char ** const result, unsigned int const number) {
    if (result == NULL) return INVALID_PARAMETER;
    int i, flag, *fib_res = NULL, count = 0, result_code;
    unsigned int num_copy = number;

    result_code = get_fibonacci_seq(&fib_res, &count, number);
    if (result_code != OK) return result_code;

    if (*result != NULL) free(*result);
    if ((*result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;

    char* buf = NULL, *p_res = *result;
    if ((buf = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;
    itoa(fib_res[count - 1], buf, 10);
    strcat(buf, "+");
    strcpy(p_res, buf);
    num_copy -= fib_res[count - 1];

    flag = 0;
    for (i = count - 2; i >= 0 && num_copy > 0; i--) {
        if((buf = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;

        if (num_copy >= fib_res[i]) {
            num_copy -= fib_res[i];
            itoa(fib_res[i], buf, 10);
            if (flag) {
                strcat(p_res, "+");
                strcat(p_res, buf);
            } else {
                strcat(p_res,  buf);
                flag = 1;
            }
        }
    }

    return OK;
}

int get_roman_representation(char ** const result, int const number) {
    if (result == NULL) return INVALID_PARAMETER;

    if (*result != NULL) free(*result);
    if ((*result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;

    char *p_res = *result;
    int i, thousands_count, hundreds_count, tens_count, units_count;

    thousands_count = number / 1000;
    for (i = 0; i < thousands_count; i++) {
        *p_res++ = 'M';
    }

    hundreds_count = (number % 1000) / 100;
    if (hundreds_count == 9) {
        *p_res++ = 'C';
        *p_res++ = 'M';
    } else if (hundreds_count == 4) {
        *p_res++ = 'C';
        *p_res++ = 'D';
    } else {
        if (hundreds_count >= 5) {
            *p_res++ = 'D';
            hundreds_count -= 5;
        }

        for (i = 0; i < hundreds_count; i++) {
            *p_res++ = 'C';
        }
    }

    tens_count = (number % 100) / 10;
    if (tens_count == 9) {
        *p_res++ = 'X';
        *p_res++ = 'C';
    } else if (tens_count == 4) {
        *p_res++ = 'X';
        *p_res++ = 'L';
    } else {
        if (tens_count >= 5) {
            *p_res++ = 'L';
            hundreds_count -= 5;
        }

        for (i = 0; i < tens_count; i++) {
            *p_res++ = 'X';
        }
    }

    units_count = number % 10;
    if (units_count == 9) {
        *p_res++ = 'I';
        *p_res++ = 'X';
    } else if (units_count == 4) {
        *p_res++ = 'I';
        *p_res++ = 'V';
    } else {
        if (units_count >= 5) {
            *p_res++ = 'V';
            units_count -= 5;
        }

        for (i = 0; i < units_count; i++) {
            *p_res++ = 'I';
        }
    }

    *p_res++ = '\0';
    puts(*result);
}