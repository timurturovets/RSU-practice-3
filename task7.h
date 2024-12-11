int check_if_numbers_are_Kaprekar(int const base, ...);
int check_if_number_is_Kaprekar(int * const result, int const base, char const * const number);

int task_7(int argc, char** argv) {
    return check_if_numbers_are_Kaprekar(10, "297", "1F", "AEA", "B52", NULL);
}

int check_if_numbers_are_Kaprekar(int const base, ...) {
    va_list p_args;
    va_start(p_args, base);

    char* arg;
    int result, result_code;
    while(1) {
        arg = va_arg(p_args, void*);
        if (arg == NULL) break;

        result_code = check_if_number_is_Kaprekar(&result, base, arg);
        switch (result_code) {
            case OK:
                puts(arg);
                printf(result ? "This is a Kaprekar number.\n\n" : "This is not a Kaprekar number.\n\n");
                break;
            case INVALID_PARAMETER:
                PRINT_INVALID_PARAMETER_MESSAGE();
                break;
            default:
                PRINT_ERROR_MESSAGE();
                return ERR;
        }
    }

    return OK;
}

/*
  # Перевести число в десятичное.
  # Возвести в квадрат.
  # Вернуть обратно в систему получившийся квадрат.
  # Разделить на две части циклом.
    # Эти части вернуть в десятичную и сложить.
    # Вторая часть не должна быть нулем
    # Результат вернуть обратно в начальную систему.
    # Проверить на равенство с начальным числом.

 */
int check_if_number_is_Kaprekar(int * const result, int const base, char const * const number) {
    if (result == NULL || number == NULL || base < 2 || base > 36) return INVALID_PARAMETER;

    int i, j, result_code,
        num_in_dec,
        square, square_str_len,
        part1_in_dec, part2_in_dec,
        parts_sum;
    char* square_str = NULL, *p_square_str,
        *part1 = NULL, *p_part1,
        *part2 = NULL, *p_part2,
        *parts_sum_str = NULL;

    result_code = from_any_to_dec(&num_in_dec, number, base);
    if (result_code != OK) return result_code;

    if ((square_str = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;

    square = num_in_dec * num_in_dec;
    result_code = from_dec_to_any(&square_str, square, base, 1);
    if (result_code != OK) {
        free(square_str);
        return result_code;
    }

    square_str_len = strlen(square_str);
    for (i = 2; i < square_str_len; i++) {
        if (part1 != NULL) free(part1);
        if (part2 != NULL) free(part2);
        if (((part1 = (char*) malloc(square_str_len * sizeof(char))) == NULL) ||
           ((part2 = (char*) malloc(square_str_len * sizeof(char))) == NULL)) {
            free(square_str);
            if (part1 != NULL) free(part1);
            return MEMORY_ALLOCATION_ERROR;
        }

        p_square_str = square_str;
        p_part1 = part1;
        p_part2 = part2;

        for (j = 0; j < i; j++) *p_part1++ = *p_square_str++;

        if (*p_square_str == '0') *p_part1++ = *p_square_str++;
        *p_part1 = '\0';

        for (j = i; j < square_str_len; j++) *p_part2++ = *p_square_str++;
        *p_part2++ = '\0';

        // ?
        result_code = from_any_to_dec(&part1_in_dec, part1, base);
        if (result_code != OK) {
            free(square_str);
            free(part1);
            free(part2);
            return result_code;
        }

        result_code = from_any_to_dec(&part2_in_dec, part2, base);
        if (result_code != OK) {
            free(square_str);
            free(part1);
            free(part2);
            return result_code;
        }

        parts_sum = part1_in_dec + part2_in_dec;

        if ((parts_sum_str = (char*) malloc(BUFSIZ * sizeof(char))) == NULL ||
            from_dec_to_any(&parts_sum_str, parts_sum, base, 1) != OK) {
            if (parts_sum_str != NULL) free(parts_sum_str);
            free(square_str);
            free(part1);
            free(part2);
            return ERR;
        }

        if (strcmp(parts_sum_str, number) == 0) {
            free(square_str);
            *result = 1;
            return OK;
        }

    }

    *result = 0;

    free(square_str);

    return OK;
}