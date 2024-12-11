int check_if_numbers_are_Kaprekar(int const base, ...);
int check_if_number_is_Kaprekar(int * const result, int const base, char const * const number);

int task_7(int argc, char** argv) {
    return check_if_numbers_are_Kaprekar(10, "45", "10A1F", "AAAAAAEEEEEEE", "B52", NULL);
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

int check_if_number_is_Kaprekar(int * const result, int const base, char const * const number) {
    if (number == NULL || base < 2 || base > 36) return INVALID_PARAMETER;

    if(strcmp(number, "1") == 0) {
        *result = 1;
        return OK;
    }

    long real_num, square;
    int i, center, flag, num_len, sqr_len;
    char * end;
    real_num = strtol(number, &end, base);
    if (*end != '\0') return INVALID_PARAMETER;

    square = real_num * real_num ;

    num_len = strlen(number);
    sqr_len = integer_len(square);

    flag = 0;
    for (i = 1; i < sqr_len; i++) {
        center = pow(base, i);
        if ((square / center) + (square % center) == real_num) {
            flag = 1;
            break;
        }
    }

    *result = flag;
    return OK;
}