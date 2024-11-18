#include <stdarg.h>

int task_2(int const argc, char** const argv) {
    if (argc < 3) {
        PRINT_INVALID_INPUT_MESSAGE();
        return INVALID_INPUT;
    }

    char** p_argv = argv;
    char* flag = *++p_argv;
    char* str = *++p_argv;

    int result_code;
    if (strcmp(flag, "-l") == 0) {
        int len;
        result_code = str_len(str, &len);
        switch (result_code) {
            case OK:
                printf("Length of the input string: %d", len);
                break;
            case INVALID_PARAMETER:
                PRINT_INVALID_PARAMETER_MESSAGE();
                break;
            default:
                PRINT_ERROR_MESSAGE();
                break;
        }
        return result_code;

    } else if (strcmp(flag, "-r") == 0) {
        result_code = str_reverse(&str);
        switch(result_code) {
            case OK:
                printf("Reversed input string: ");
                puts(str);
                return OK;
            case INVALID_PARAMETER:
                PRINT_INVALID_PARAMETER_MESSAGE();
                return INVALID_PARAMETER;
            default:
                PRINT_ERROR_MESSAGE();
        }

    } else if (strcmp(flag, "-u") == 0) {
        result_code = change_characters_case(&str);
        if(result_code == OK) {
            printf("Input string with every odd-placed character's case made upper: ");
            puts(str);
            return OK;
        } else {
            PRINT_ERROR_MESSAGE();
            return result_code;
        }
    } else if (strcmp(flag, "-n") == 0) {

    } else if (strcmp(flag, "-c") == 0) {

    } else {
        printf("Error: invalid flag. Please restart the program and pass proper flag value.");
        return INVALID_PARAMETER;
    }
}