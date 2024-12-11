#include <string.h>
int get_roman_representation(char ** const result, int const number);

int task_9(int argc, char** argv) {
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

    from_dec_to_any(&result, number, 16, 1);
    printf("to base result: ");
    puts(result);

    int code = from_any_to_dec(&number, "1F",16);
    printf("test result: %d", number);

    free(result);
    return OK;
}