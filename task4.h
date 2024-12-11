#include <stdlib.h>
#include "auxiliary.h"

int search_str_in_files(char*, ...);
int search_str_in_file(char const * const substr,
                       char const * const file_path,
                       size_t* result_count,
                       int ** result_rows,
                       int ** result_columns);

int task_4(int argc, char** argv) {
    char* substr = (char*) malloc(sizeof(char) * BUFSIZ + 1);
    if (substr == NULL) {
        PRINT_MEMORY_ALLOCATION_ERROR();
        return MEMORY_ALLOCATION_ERROR;
    }

    printf("Enter your substring: ");
    gets(substr);
    printf("\n");

    int len;
    int result_code = str_len(substr, &len); //declared in auxiliary.h
    if(result_code != OK || len == 0) {
        PRINT_INVALID_INPUT_MESSAGE();
        return INVALID_INPUT;
    }

    char *file1_path = "D:\\meow.txt", *file2_path = "D:\\bzz.txt", *file3_path = "D:\\bark.txt";

    result_code = search_str_in_files(substr, file1_path, file2_path, file3_path, NULL);
    switch (result_code) {
        case OK:
            return OK;
        case INVALID_PARAMETER:
            PRINT_INVALID_PARAMETER_MESSAGE();
            return INVALID_PARAMETER;
        case INVALID_INPUT:
            PRINT_INVALID_INPUT_MESSAGE();
            return INVALID_INPUT;
        case MEMORY_ALLOCATION_ERROR:
            PRINT_MEMORY_ALLOCATION_ERROR();
            return MEMORY_ALLOCATION_ERROR;
        default:
            PRINT_ERROR_MESSAGE();
            return ERR;
    }
}

int search_str_in_files(char* substr, ...) {
    if (substr == NULL) return INVALID_PARAMETER;

    va_list p_args;
    va_start(p_args, substr);

    char const* arg;
    int* result_rows = NULL, *result_columns = NULL;
    while(1) {
        arg = va_arg(p_args, void*);
        if (arg == NULL) break;

        size_t count = 0;
        int result_code = search_str_in_file(substr, arg, &count, &result_rows, &result_columns);
        switch(result_code) {
            case OK:
                printf("File path: ");
                puts(arg);
                if (count == 0) printf("Your substring is not present in the file.\n\n");
                else {
                    printf("Your substring is found in the file at:\n");
                    for (int i = 0; i < count; i++) {
                        printf("Row: %d, column: %d\n", result_rows[i], result_columns[i]);
                    }
                    printf("\n");
                }
                break;
            default:
                PRINT_ERROR_MESSAGE();
                break;
        }
    }

    va_end(p_args);
    free(result_rows);
    free(result_columns);
    return OK;
}

int search_str_in_file(const char * const substr, const char * const file_path, size_t* result_count,
                       int ** result_rows, int ** result_columns) {
    if(substr == NULL || file_path == NULL) return INVALID_PARAMETER;

    FILE* f_ptr = NULL;
    if ((f_ptr = fopen(file_path, "r")) == NULL) return INVALID_PARAMETER;

    if (*result_rows != NULL) free(*result_rows);
    if (*result_columns != NULL) free(*result_columns);

    *result_rows = (int*) malloc(BUFSIZ * sizeof(int));
    *result_columns = (int*) malloc(BUFSIZ * sizeof(int));
    if(result_rows == NULL || result_columns == NULL) return MEMORY_ALLOCATION_ERROR;
    int* p_res_rows = *result_rows, *p_res_cols = *result_columns;

    char curr_c;
    char const * p_sub = substr;
    int row = 1, col = 0, start_row, start_col;

    int len, result_code;
    result_code = str_len(substr, &len);
    if(result_code != OK) return result_code;

    while(!feof(f_ptr)) {
        fscanf(f_ptr, "%c", &curr_c);
        col++;

        if (curr_c == '\n') {
            row++;
            col = 0;
        }

        if (curr_c == *p_sub) {
            p_sub++;
            start_row = row;
            start_col = col;

            int i, flag = 1;

            for(i = 1; i < len; i++) {
                fscanf(f_ptr, "%c", &curr_c);
                col++;
                if (curr_c == '\n') {
                    row++; col = 0;
                }

                if (curr_c != *p_sub++) {
                    flag = 0;
                    p_sub = substr;
                    break;
                }
            }

            if (flag) {
                *p_res_rows++ = start_row;
                *p_res_cols++ = start_col;
                (*result_count)++;

                p_sub = substr;
            }
        }
    }
    return OK;
}