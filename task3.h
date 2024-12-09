#include <stdio.h>
#include <stdarg.h>

int multiple_free(int flag, ...);

int task_3() {
    FILE* file1 = fopen("file1.txt", "w");
    char* resource1 = (char*) malloc(BUFSIZ * sizeof(char));
    int* resource2 = (int*) malloc(256 * sizeof(int));

    if (file1 == NULL || resource1 == NULL || resource2 == NULL) {
        PRINT_INVALID_INPUT_MESSAGE();
        return INVALID_INPUT;
    }

    int result_code = multiple_free('f', file1, 'm', resource2, 'f', resource1, 'q', NULL);
    switch (result_code){
        case OK:
            printf("Program complete.\n");
            break;
        case INVALID_PARAMETER:
            PRINT_INVALID_PARAMETER_MESSAGE();
            break;
        default:
            PRINT_ERROR_MESSAGE();
    }
    return result_code;
}

int multiple_free(int flag, ...) {
    if (flag != 'f' && flag != 'm') return INVALID_PARAMETER;

    va_list p_args;
    va_start(p_args, flag);

    while (1) {
        void* resource = va_arg(p_args, void*);

        if(resource == NULL) {
            va_end(p_args);
            return OK;
        }

        if (flag == 'm') {
            printf("Freeing memory at address %p\n", resource);
            free(resource);
        } else if (flag == 'f') {
            printf("Closing file at address %p\n", resource);
            fclose(resource);
        } else {
            va_end(p_args);
            return INVALID_PARAMETER;
        }

        flag = va_arg(p_args, int);
    }


}