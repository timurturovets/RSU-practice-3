#include <stdarg.h>

int change_characters_case(char** str);
int shift_characters(char** str);
int random_concat(char** strings, int count, unsigned int seed, char** result);

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
        int str_count = argc - 3; // 3 extra arguments: path, flag and seed;

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

        char* result = NULL;
        result_code = random_concat(strings, str_count, seed, &result);
        switch (result_code) {
            case OK:
                printf("After randomly concatenating input strings: ");
                puts(result);
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
        free(result);
        free(strings);
        return result_code;
    } else {
        printf("Error: invalid flag. Please restart the program and pass proper flag value.");
        return INVALID_PARAMETER;
    }
}

int change_characters_case(char** str) {
    if(str == NULL || *str == NULL) return INVALID_PARAMETER;

    int len, result_code;
    if ((result_code = str_len(*str, &len)) != OK) return result_code;

    int dumb_counter = 0;
    for(char* p_str = *str; *p_str != '\0'; p_str++) {
        if (dumb_counter++ % 2 == 0) continue;
        *p_str = toupper(*p_str);
    }
    return OK;
}

int shift_characters(char** str) {
    if (str == NULL || *str == NULL) return INVALID_PARAMETER;

    int len, result_code;
    if((result_code = str_len(*str, &len)) != OK) return result_code;
    if(len == 0) return INVALID_PARAMETER;

    char* result = NULL;
    if ((result = (char*) malloc(sizeof(char) * len + 1)) == NULL) return MEMORY_ALLOCATION_ERROR;

    char* p_result = result;
    char* p_str = *str;
    for(; *p_str != '\0'; p_str++) if (isdigit(*p_str)) *p_result++ = *p_str;

    for (p_str = *str; *p_str != '\0'; p_str++) if (isalpha(*p_str)) *p_result++ = *p_str;

    for (p_str = *str; *p_str != '\0'; p_str++) if(!isdigit(*p_str) && !isalpha(*p_str)) *p_result++ = *p_str;

    *p_result++ = '\0';
    *str = result;

    return OK;
}


int random_concat(char** strings, int count, unsigned int seed, char** result) {
    if(strings == NULL || count == 0) return INVALID_PARAMETER;

    if (*result != NULL) free(*result);
    srand(seed);

    int* checked = NULL;
    if((checked = (int*) malloc(sizeof(int) * count)) == NULL) return MEMORY_ALLOCATION_ERROR;
    int* p_checked = checked;

    char** p_strings = strings;
    char* new_string = NULL;
    if((new_string = (char*) malloc(sizeof(char) * BUFSIZ * count + 1)) == NULL) return MEMORY_ALLOCATION_ERROR;
    char* p_newstr = new_string;
    int i, random_index;
    for(i = 0; i < count; i++) {
        do {
            random_index = rand() % (count);
        } while(is_in_array(checked, count, random_index));
        *p_checked++ = random_index;

        char* current_str = p_strings[random_index];

        char* p_currstr = current_str;

        for(; *p_currstr != '\0'; p_currstr++) {
            *p_newstr++ = *p_currstr;
        }
    }
    *result = new_string;

    return OK;
}