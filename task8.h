int notation_sum(char ** const result, int const base, int const count, ...);
int sum_in_base(char ** const result, int const base, char const * const num_1, char const * const num_2);

int task_8(int argc, char** argv) {
    char* result = (char*)malloc(sizeof(char) * BUFSIZ);

    if (result == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    int result_code = notation_sum(&result, 16, 3, "11111AAADD1", "DDDDDDDEEE", "7381950CCCCC");

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

    /*if ((temp_sum = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) {
        free(sum);
        return MEMORY_ALLOCATION_ERROR;
    }*/

    prev = (char*) va_arg(p_args, void*);
    if (prev == NULL) {
        free(sum);
        //free(temp_sum);
        return INVALID_PARAMETER;
    }

    for (i = 1; i < count; i++) {
        arg = (char*) va_arg(p_args, void*);
        if(arg == NULL) break;

        puts(arg);
        printf("and prev here: ");
        puts(prev);
        result_code = sum_in_base(&temp_sum, base, prev, arg);
        if (result_code != OK) {
            if(sum != NULL) free(sum);
            return result_code;
        }
//        printf("temp sum: ");
//        puts(temp_sum);

        prev = (char*) malloc(BUFSIZ * sizeof(char));
        strcpy(prev, temp_sum);

//        printf("prev: ");
//        puts(prev);
    }

    *result = prev;

    return OK;
}

int sum_in_base(char ** const result, int const base, char const * const num_1, char const * const num_2) {
    if (result == NULL || num_1 == NULL || num_2 == NULL || base < 2 || base > 36) return INVALID_PARAMETER;
    printf("received: ");
    puts(num_1);
    puts(num_2);
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
        i, j, Z, V,
        digit_1, digit_2,
        sum, carry = 0,
        flag = 0;
    printf("received 5: ");
    puts(num_1);
    int const DIG_LEN = strlen(all_digits);

    printf("num1 1: ");
    puts(num_1);
    len_1 = strlen(num_1);
    printf("num1 2: ");
    puts(num_1);
    len_2 = strlen(num_2);
    max_len = len_1 > len_2 ? len_1 : len_2;

    i = len_1 - 1;
    j = len_2 - 1;
    V = max_len;
    printf("nums: \n");
    puts(num_1);
    puts(num_2);
    printf("\n");
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

        printf("we got %d+%d=%d, carry: %d, digits: %c, %c\n", digit_1, digit_2, sum, carry, num_1[i], num_2[j]);
        flag = carry;
        carry = sum / base;

        p_alldig = all_digits;
        for (Z = 0; Z < DIG_LEN; Z++) {
            if (*p_alldig++ == dtoc(sum % base)) {
                sum = Z;
                printf("having sum as %d, ", Z);
                break;
            }
        }

        //p_result[V--] = dtoc(sum);
        *p_result++ = dtoc(sum);
        printf("added %c to res\ni: %d, j: %d, carry: %d\n\n", dtoc(sum), i, j, carry);

        i--;
        j--;
    }
    *p_result = '\0';

    printf("\nafter shit carry: %d, zetochka: %d, SVO: ", carry, flag);
    puts(pre_result);
    max_len = strlen(pre_result);

    p_result = *result;


    printf("maxlen: %d\n", max_len);
    for (i = max_len - 1; i >= 0; i--) {
        *p_result++ = pre_result[i];
        printf("v momente: %c, ", pre_result[i]);
    }
    /*while(*++pre_result) {
        *p_result++ = *pre_result;
        printf("doing %c, ", *pre_result);
    }*/
    *p_result = '\0';
    printf("\n");
    printf("after all the shit: ");
    puts(*result);
}
