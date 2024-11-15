#pragma once
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "auxiliary.h"

int from_decimal_to_binary(int const num, int const radix, char* const result_ptr) {
    if (radix < 1 || radix > 5) return INVALID_PARAMETER;

    int num_copy = abs(num), real_radix = pow(2, radix);

    char* result = NULL;
    if((result = (char*) malloc((BUFSIZ+1) * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;
    char* presult = result;

    char* buf = NULL;
    if((buf = (char*) malloc(sizeof(char)*2)) == NULL) {
        free(result);
        return MEMORY_ALLOCATION_ERROR;
    }

    while(num_copy != 0) {
        itoa(num_copy & (real_radix - 1), buf, real_radix);
        *presult++ = *buf;
        num_copy >>= radix;
    }

    if (num < 0) *presult++ = '-';
    *presult = '\0';
    int result_code = str_reverse(result);
    switch(result_code) {
        case OK:
            strcpy(result_ptr, result);
            free(buf);
            free(result);
            return OK;

        default:
            free(buf);
            free(result);
            return ERR;
    }
}

int task_1() {
    int num, radix;

    printf("Input your number: ");
    if(scanf("%d", &num) != 1) {
        printf("Error: entered value is invalid.");
        return INVALID_INPUT;
    }

    printf("Input your power of 2: ");
    if(scanf("%d", &radix) != 1) {
        printf("Error: entered value is invalid.");
        return INVALID_INPUT;
    }
    char* result = NULL;
    if((result = (char*) malloc(sizeof(char) * BUFSIZ + 1)) == NULL) {
        printf("Error: couldn't allocate memory. Restarting the program may help.");
        return MEMORY_ALLOCATION_ERROR;
    }

    int result_code = from_decimal_to_binary(num, radix, result);
    switch(result_code) {
        case OK:
            printf("Result: ");
            puts(result);
            free(result);
            return OK;

        case INVALID_PARAMETER:
            printf("Error: invalid parameter. Conditions: 1 <= radix <= 5");
            free(result);
            return INVALID_PARAMETER;

        case MEMORY_ALLOCATION_ERROR:
            printf("Error: couldn't allocate memory. Restarting the program may help.");
            free(result);
            return MEMORY_ALLOCATION_ERROR;

        default:
            printf("Error: unforeseen error. Restarting the program may help.");
            free(result);
            return ERR;
    }
}

// input data validation +
// functions parameters quantity validation +
// memory allocation validation
// memory release
// functions error codes, handling
// comparing doubles with epsilon 0
// restrain parameters modification in functions