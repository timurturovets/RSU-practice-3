int notation_sum(char ** const result, int const base, int const count, ...);
int sum_in_base(char ** const result, int const base, char const * const num_1, char const * const num_2);

int task_8() {
    char* result = (char*)malloc(sizeof(char) * BUFSIZ);

    if (result == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    int result_code = notation_sum(&result, 16, 4, "AAAAAA00090894225", "CCCCCCCCCCCCCCCCCC525", "71555");

    switch(result_code) {
        case OK:
            printf("Resulting sum: ");
            puts(result);
            break;
        case MEMORY_ALLOCATION_ERROR:
            PRINT_MEMORY_ALLOCATION_ERROR();
            break;
        case INVALID_PARAMETER:
            PRINT_INVALID_PARAMETER_MESSAGE();
            break;
        default:
            PRINT_ERROR_MESSAGE();
            break;
    }

    free(result);

    return result_code;
}

int notation_sum(char ** const result, int const base, int const count, ...) {
    if (base < 2 || base > 36 || count < 2) return INVALID_PARAMETER;

    int i, result_code;
    va_list p_args;
    va_start(p_args, count);

    char *arg, *prev;
    char *sum = NULL;
    printf("Numbers:\n");
    prev = (char*) va_arg(p_args, void*);
    puts(prev);
    if (prev == NULL) return INVALID_PARAMETER;

    for (i = 1; i < count; i++) {
        arg = (char*) va_arg(p_args, void*);
        if(arg == NULL) break;
        puts(arg);
        result_code = sum_in_base(&sum, base, prev, arg);
        if (result_code != OK) {
            if(sum != NULL) free(sum);
            return result_code;
        }

        prev = sum;
    }

    *result = prev;

    return OK;
}

int sum_in_base(char ** const result, int const base, char const * const num_1, char const * const num_2) {
    if (result == NULL || base < 2 ||  base > 36 || num_1 == NULL || num_2 == NULL) return INVALID_PARAMETER;
    int len_1, len_2, mxl,
        i, m, n,
        carry, sum;

    mxl = len_1 = strlen(num_1);
    len_2 = strlen(num_2);
    if (len_2 > mxl) mxl = len_2;

    *result = (char*) malloc(sizeof(char) * (len_1 + len_2) * 2);
    if (result == NULL) return MEMORY_ALLOCATION_ERROR;

    i = mxl - 1;
    m = len_1 - 1;
    n = len_2 - 1;
    carry = 0;

    while (i >= 0) {
        int d1 = m >= 0 ? ctod(num_1[m]) : 0,
            d2 = n >= 0 ? ctod(num_2[n]) : 0;

            sum = d1 + d2 + carry;
            carry = sum / base;
            (*result)[i] = dtoc(sum % base);
            i--; m--; n--;
    }
    int l = strlen(*result);
    char* new_r = (char*) malloc(l * sizeof(char) + 1);

    if(new_r == NULL) return MEMORY_ALLOCATION_ERROR;

    if (carry > 0) {
        new_r[0] = dtoc(carry);

        for(i = 1; i < l; i++) new_r[i] = (*result)[i - 1];

        new_r[i - 2] = '\0';

        free(*result);

        *result = new_r;
    } else (*result)[l - 3] = '\0';
    return OK;
}