#pragma once
#include <string.h>

#define OK 0
#define ERR (-1)
#define INVALID_INPUT (-2)
#define INVALID_PARAMETER (-3)
#define MEMORY_ALLOCATION_ERROR (-4)

int str_reverse(char* str) {
    if (str == NULL || strlen(str) == 0) return INVALID_PARAMETER;

    int start = 0, end = strlen(str) - 1;

    char t;
    while (start < end) {
        t = str[start];
        str[start] = str[end];
        str[end] = t;
        start++; end--;
    }

    return OK;
}