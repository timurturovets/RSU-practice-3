int notation_sum(char ** const result, int const base, int const count, ...);
int sum_in_base(char ** const result, int const base, char const * const num_1, char const * const num_2);

int task_8(int argc, char** argv) {
    char* result = (char*)malloc(sizeof(char) * BUFSIZ);

    if (result == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    int result_code = notation_sum(&result, 16, 3, "BBBB11111AAADD1", "DDDDDDDEEE", "7381950CCCCC");

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

    char *arg, *prev, *sum, *temp_sum;

    if ((sum = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;

    prev = (char*) va_arg(p_args, void*);
    if (prev == NULL) {
        free(sum);
        return INVALID_PARAMETER;
    }

    for (i = 1; i < count; i++) {
        arg = (char*) va_arg(p_args, void*);
        if(arg == NULL) break;

        result_code = sum_in_base(&temp_sum, base, prev, arg);
        if (result_code != OK) {
            if(sum != NULL) free(sum);
            return result_code;
        }

        prev = (char*) malloc(BUFSIZ * sizeof(char));
        strcpy(prev, temp_sum);
    }

    *result = prev;

    return OK;
}

int sum_in_base(char ** const result, int const base, char const * const num_1, char const * const num_2) {
    if (result == NULL || num_1 == NULL || num_2 == NULL || base < 2 || base > 36) return INVALID_PARAMETER;

    char *pre_result,
            *all_digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", *p_alldig,
            *p_result;

    if ((pre_result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;

    if (*result != NULL) free(*result);

    if ((*result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) {
        free(pre_result);
        return MEMORY_ALLOCATION_ERROR;
    }

    int len_1, len_2, max_len,
            i, j, Z,
            digit_1, digit_2,
            sum, carry = 0;
    int const DIG_LEN = strlen(all_digits);

    len_1 = strlen(num_1);

    len_2 = strlen(num_2);
    max_len = len_1 > len_2 ? len_1 : len_2;

    i = len_1 - 1;
    j = len_2 - 1;

    p_result = pre_result;
    while (i >= 0 || j >= 0 || carry) {
        p_alldig = all_digits;

        digit_1 = 0;
        if (i >= 0) {
            for (Z = 0; Z < DIG_LEN; Z++) {
                if (*p_alldig++ == num_1[i]) digit_1 = Z;
            }
        }
        p_alldig = all_digits;
        digit_2 = 0;
        if (j >= 0) {
            for (Z = 0; Z < DIG_LEN; Z++) {
                if (*p_alldig++ == num_2[j]) {
                    digit_2 = Z;
                    break;
                }
            }
        }
        sum = digit_1 + digit_2 + carry;

        carry = sum / base;

        p_alldig = all_digits;
        for (Z = 0; Z < DIG_LEN; Z++) {
            if (*p_alldig++ == dtoc(sum % base)) {
                sum = Z;
                break;
            }
        }

        *p_result++ = dtoc(sum);

        i--;
        j--;
    }
    *p_result = '\0';

    max_len = strlen(pre_result);

    p_result = *result;

    for (i = max_len - 1; i >= 0; i--) {
        *p_result++ = pre_result[i];
    }

    *p_result = '\0';

    //puts(*result);
    return OK;
}