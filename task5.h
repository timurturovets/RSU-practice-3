int is_convex(int* result, int count, ...);

int task_5() {
    int result_code, result;
    result_code = is_convex(&result, 8, 1.431, 3.333333333, 10.9494, 11.34, 41.61351, 5316.53151, 99.876, 5.4321);

    switch(result_code) {
        case OK:
            if (result) printf("Your polygon is convex.\n");
            else printf("Your polygon isn't convex.\n");
            break;
        case INVALID_PARAMETER:
            PRINT_INVALID_PARAMETER_MESSAGE();
            break;
        case MEMORY_ALLOCATION_ERROR:
            PRINT_MEMORY_ALLOCATION_ERROR();
            break;
        default:
            PRINT_ERROR_MESSAGE();
    }
    return result_code;
}

int is_convex(int* result, int count, ...) {
    if (count < 3 || count % 2 != 0) return INVALID_PARAMETER;

    int const pairs_count = count / 2;

    double *points_x = NULL, *points_y = NULL;
    points_x = (double *) malloc(pairs_count * sizeof(double));
    points_y = (double *) malloc(pairs_count * sizeof(double));
    if (points_x == NULL || points_y == NULL) return MEMORY_ALLOCATION_ERROR;
    double *p_x = points_x, *p_y = points_y;

    va_list p_args;
    va_start(p_args, count);
    double arg;
    int i;
    for (i = 0; i < pairs_count; i++) {
        arg = va_arg(p_args, double);
        *p_x++ = arg;

        arg = va_arg(p_args, double);
        *p_y++ = arg;
    }
    va_end(p_args);

    p_x = points_x;
    p_y = points_y;
    double start_x = *p_x++, start_y = *p_y++,
            curr_x, curr_y,
            next_x, next_y,
            vec_x, vec_y,
            nvec_x, nvec_y,
            det;

    for (i = 1; i < pairs_count; i++) {
        curr_x = p_x[i];
        curr_y = p_y[i];

        vec_x = curr_x - start_x;
        vec_y = curr_y - start_y;

        next_x = p_x[(i + 1) % pairs_count];
        next_y = p_y[(i + 1) % pairs_count];

        nvec_x = next_x - start_x;
        nvec_y = next_y - start_y;

        det = vec_x * nvec_y - nvec_x * vec_y;

        if (det <= 0) {
            *result = 0;

            free(points_x);
            free(points_y);

            return OK;
        }
    }

    *result = 1;

    free(points_x);
    free(points_y);

    return OK;
}