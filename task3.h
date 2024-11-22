#include <stdio.h>
#include <stdarg.h>

int multiple_free(int flag, ...);

int task_3() {
    FILE* file1 = fopen("file1.txt", "w");
    FILE* file2 = fopen("file2.txt", "r");
    char* resource1 = (char*) malloc(BUFSIZ * sizeof(char));
    int* resource2 = (int*) malloc(256 * sizeof(int));

    if (file1 == NULL || file2 == NULL || resource1 == NULL || resource2 == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    int result_code = multiple_free('f', file1, 'm', resource2, 'f', file2, 'm', resource1, 'q', NULL);
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

    while (1) {
        void* resource = va_arg(p_args, void*);

        if(resource == NULL) return OK;

        if (flag == 'm') {
            printf("Freeing memory at address %p\n", resource);
            free(resource);
        } else if (flag == 'f') {
            printf("Closing file at address %p\n", resource);
            fclose(resource);
        } else return INVALID_PARAMETER;

        flag = va_arg(p_args, int);
    }


}