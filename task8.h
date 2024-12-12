int notation_sum(char ** const result, int const base, int const count, ...);
int sum_in_base(char ** const result, int const base, char const * const num_1, char const * const num_2);

int task_8(int argc, char** argv) {
    char* result = (char*)malloc(sizeof(char) * BUFSIZ);

    if (result == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    int result_code = notation_sum(&result, 16, 2, "12AB9", "4DD96");

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
    if (result == NULL || num_1 == NULL || num_2 == NULL || base < 2 || base > 36) return INVALID_PARAMETER;

    char *prev_result,
        *all_digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", *p_alldig,
        *p_result;

    if ((prev_result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;

    if (*result != NULL) free(*result);
    if ((*result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) {
        free(prev_result);
        return MEMORY_ALLOCATION_ERROR;
    }

    int len_1, len_2, max_len,
        i, j, k, Z, V,
        digit_1, digit_2,
        sum, carry = 0;

    int const DIG_LEN = strlen(all_digits);

    len_1 = strlen(num_1);
    len_2 = strlen(num_2);
    max_len = len_1 > len_2 ? len_1 : len_2;

    i = len_1 - 1;
    j = len_2 - 1;
    k = max_len;
    printf("nums: \n");
    puts(num_1);
    puts(num_2);
    printf("\n");
    p_result = prev_result;
    while (i >= 0 || j >= 0 || carry ) {
        p_alldig = all_digits;

        digit_1 = -1;
        for (Z = 0; Z < DIG_LEN; Z++) {
            if (*p_alldig++ == num_1[i]) digit_1 = Z;
        }

        p_alldig = all_digits;
        digit_2 = -1;
        for (Z = 0; Z < DIG_LEN; Z++) {
            if (*p_alldig++ == num_2[i]) {
                digit_2 = Z;
                break;
            }
        }

        sum = digit_1 + digit_2 + carry;
        carry = sum / base;

        p_alldig = all_digits;
        printf("we got %d\n", sum % base);
        for (Z = 0; Z < DIG_LEN; Z++) {
            if (*p_alldig++ == dtoc(sum % base)) {
                sum = Z;
                printf("having sum as %d, ", Z);
                break;
            }
        }

        p_result[k--] = dtoc(sum);
        printf("added %c to res\n", dtoc(sum));
        i--;
        j--;
    }
    printf("after shit: ");
    puts(prev_result);

    p_result = *result;
    while(*++prev_result) {
        *p_result++ = *prev_result;
        printf("doing %c\n", *prev_result);
    }
    *p_result = '\0';

    printf("after all the shit: ");
    puts(*result);
}

/*
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
}*/