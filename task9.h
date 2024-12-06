#include <string.h>
int get_roman_representation(char ** const result, int const number);

int task_9() {
    char* result = NULL;
    if((result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    int number;
    printf("num: ");
    scanf("%d", &number);
    // done
    get_zeckendorf_representation(&result, number);
    printf("zeckendorf result: ");
    puts(result);

    //done
    get_roman_representation(&result, number);
    printf("roman result: ");
    puts(result);

    to_any(&result, number, 16, 1);
    printf("to base result: ");
    puts(result);

    free(result);
    return OK;
}