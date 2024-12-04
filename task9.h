#include <string.h>

int get_zeckendorf_representation(char ** const result, unsigned int const number);

int task_9() {
    char* result = NULL;
    if((result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    get_zeckendorf_representation(&result, 301);
    printf("result: ");
    puts(result);
}

int get_zeckendorf_representation(char ** const result, unsigned int const number) {
    int i, flag, *fib_res = NULL, count = 0, result_code;
    unsigned int num_copy = number;

    result_code = get_fibonacci_seq(&fib_res, &count, number);
    if (result_code != OK) return result_code;

    if (*result != NULL) free(*result);
    if ((*result = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;

    flag = 0;
    char* buf = NULL, *p_res = *result;
    if ((buf = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;
    itoa(fib_res[count - 1], buf, 10);
    printf("first buf: ");
    strcat(buf, "+");
    puts(buf);
    strcpy(p_res, buf);
    for (i = count - 2; i >= 0 && num_copy > 0; i--) {
        if((buf = (char*) malloc(BUFSIZ * sizeof(char))) == NULL) return MEMORY_ALLOCATION_ERROR;

        if (num_copy >= fib_res[i]) {
            num_copy -= fib_res[i];
            printf("%d\n", fib_res[i]);
            itoa(fib_res[i], buf, 10);
            if (flag) {
                strcat(p_res, "+");
                strcat(p_res, buf);
            } else {
                strcat(p_res,  buf);
                flag = 1;
            }
        }
    }
    puts(*result);
    return OK;
}