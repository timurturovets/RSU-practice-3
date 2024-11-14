#pragma once
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "auxiliary.h"

int from_decimal_to_binary(int const num, int r, char* result_ptr) {
    if (r < 1 || r > 5) return INVALID_PARAMETER;
    int num_copy = abs(num), radix = pow(2, r);

    char* result = NULL;
    if((result = (char*) malloc((BUFSIZ+1) * sizeof(char))) == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    char* presult = result,
        * buf = (char*) malloc(sizeof(char)*2);

    while(num_copy != 0) {
        itoa(num_copy & (radix-1), buf, radix);
        *presult++ = *buf;
        num_copy >>= r;
    }

    if (num < 0) *presult++ = '-';
    *presult = '\0';
    str_reverse(result);

    strcpy(result_ptr, result);
    return OK;
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

    char** result = (char**) malloc(sizeof(char*) * BUFSIZ + 1);

    int result_code = from_decimal_to_binary(num, radix, result);
    switch(result_code) {
        case OK:
            printf("Result: ");
            puts(result);
            return OK;
        case INVALID_PARAMETER:
            printf("Error: invalid parameter. Conditions: 1 <= radix <= 5");

    }
    printf("result: ");
    puts(result);
}

// input data validation +
// functions parameters quantity validation +
// memory allocation validation
// memory release validation
// functions error codes, handling
// comparing doubles with epsilon
// restrain parameters modification in functions