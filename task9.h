#include <string.h>
int get_roman_representation(char ** const result, int const number);

int task_9(int argc, char** argv) {
    char* result = NULL;
    if((result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    int code, number;
    printf("num: ");
    scanf("%d", &number);

    /*get_Zeckendorf_representation(&result, number);
    printf("zeckendorf result: ");
    puts(result);

    get_roman_representation(&result, number);
    printf("roman result: ");
    puts(result);

    from_dec_to_any(&result, number, 16, 1);
    printf("to base result: ");
    puts(result);

    from_any_to_dec(&number, "1F",16);
    printf("from base result: %d\n", number);*/

    get_int_mem_dump(&result, number);
    printf("int mem dump result: ");
    puts(result);

    free(result);
    return OK;
}