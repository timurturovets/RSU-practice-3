#pragma once
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "auxiliary.h"

int from_decimal_to_binary(int const num, int const radix, char ** const result) {
    if (result == NULL || radix < 1 || radix > 5) return INVALID_PARAMETER;

    int i,
        num_copy = abs(num),
        real_radix = 1 << radix,
        digits_len = 0;

    unsigned short *digits = NULL, *p_digits;
    char *p_result, *all_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (*result != NULL) free(*result);
    if ((*result = (char*) malloc((BUFSIZ + 1) * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;
    p_result = *result;
    if ((digits = (unsigned short *) malloc(BUFSIZ * sizeof(unsigned short))) == NULL) {
        free(result);
        return MEMORY_ALLOCATION_ERROR;
    }
    p_digits = digits;

    while (num_copy != 0) {
        *p_digits++ = num_copy & (real_radix - 1);
        num_copy >>= radix;
        digits_len++;
    }

    if (num < 0) *p_result++ = '-';

    for (i = digits_len - 1; i >= 0; i--) {
        *p_result++ = all_chars[digits[i]];
    }
    *p_result = '\0';

    free(digits);

    return OK;
}

int task_1() {
    int num, radix;

    printf("Input your number: ");
    if(scanf("%d", &num) != 1) {
        PRINT_INVALID_INPUT_MESSAGE();
        return INVALID_INPUT;
    }

    printf("Input your power of 2: ");
    if(scanf("%d", &radix) != 1) {
        PRINT_INVALID_INPUT_MESSAGE();
        return INVALID_INPUT;
    }
    char* result = NULL;
    if((result = (char*) malloc(sizeof(char) * BUFSIZ + 1)) == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    int result_code = from_decimal_to_binary(num, radix, &result);
    switch(result_code) {
        case OK:
            printf("Result: ");
            puts(result);
            break;
        case INVALID_PARAMETER:
            PRINT_INVALID_PARAMETER_MESSAGE();
            break;
        case MEMORY_ALLOCATION_ERROR:
            PRINT_MEMORY_ALLOCATION_ERROR();
            break;
        default:
            PRINT_MEMORY_ALLOCATION_ERROR();
            break;
    }

    free(result);

    return result_code;
}