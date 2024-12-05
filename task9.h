#include <string.h>
int get_roman_representation(char ** const result, int const number);

int task_9() {
    char* result = NULL;
    if((result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    // done
    get_zeckendorf_representation(&result, 1300);
    printf("zeckendorf result: ");
    puts(result);

    //done
    get_roman_representation(&result, 34597);
    printf("roman result: ");
    puts(result);



    free(result);
    return OK;
}