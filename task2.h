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
                break;
            case INVALID_PARAMETER:
                PRINT_INVALID_PARAMETER_MESSAGE();
                break;
            case MEMORY_ALLOCATION_ERROR:
                PRINT_MEMORY_ALLOCATION_ERROR();
                break;
            default:
                PRINT_ERROR_MESSAGE();
                break;
        }

        return result_code;

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
        result_code = shift_characters(&str);
        switch (result_code) {
            case OK:
                printf("Input string after tidy-shifting all characters: ");
                puts(str);
                break;
            case INVALID_PARAMETER:
                PRINT_INVALID_PARAMETER_MESSAGE();
                break;
        }
        return result_code;

    } else if (strcmp(flag, "-c") == 0) {
        char** strings = NULL;
        int i, str_count = argc - 3; // 3 extra arguments: path, flag and seed;

        if ((strings = (char**) malloc(sizeof(char*) * argc)) == NULL) {
            PRINT_MEMORY_ALLOCATION_ERROR();
            return MEMORY_ALLOCATION_ERROR;
        }

        char* c_seed = *++p_argv;
        if (!isdigit(*c_seed)) {
            PRINT_INVALID_INPUT_MESSAGE();
            return INVALID_INPUT;
        }
        int seed = atoi(c_seed);

        p_argv++;

        char** p_strings = strings;
        *p_strings++ = str;
        int aux_counter = 0;
        for(; aux_counter++ < str_count; p_strings++) {
            if ((*p_strings = (char*) malloc(sizeof(char) * BUFSIZ + 1)) == NULL) {
                PRINT_MEMORY_ALLOCATION_ERROR();
                return MEMORY_ALLOCATION_ERROR;
            }
            *p_strings = *p_argv++;
        }

        char* result = (char*) malloc(sizeof(char) * BUFSIZ * str_count + 1);
        result_code = random_concat(strings, str_count, seed, &result);
        switch (result_code) {
            case OK:
                printf("After randomly concatenating input strings: ");
                puts(result);
                break;
        }

    } else {
        printf("Error: invalid flag. Please restart the program and pass proper flag value.");
        return INVALID_PARAMETER;
    }
}