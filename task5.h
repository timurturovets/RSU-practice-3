int is_convex(int* result, int count, ...);

int task_5(int argc, char** argv) {
    int result_code, result;
    result_code = is_convex(&result, 3, 0.0, 0.0, 2.0, 2.0, 5.0, 0.0);

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

int is_convex(int * const result, int const count, ...) {
    if (result == NULL || count < 3) return INVALID_PARAMETER;

    va_list p_args;
    va_start(p_args, count);

    int i, turn_direction = 0;
    double prod,
           x1, y1,
           x2, y2,
           x3, y3;

    for (i = 0; i < count - 2; i++) {
        if (i == 0) {
            x1 = va_arg(p_args, double);
            y1 = va_arg(p_args, double);
            x2 = va_arg(p_args, double);
            y2 = va_arg(p_args, double);
        } else {
            x1 = x2;
            y1 = y2;
            x2 = x3;
            y2 = y3;
        }

        x3 = va_arg(p_args, double);
        y3 = va_arg(p_args, double);

        prod = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
        if (prod == 0) continue;

        if (turn_direction == 0) {
            turn_direction = prod > 0 ? 1 : -1;
            continue;
        }

        if (!((prod > 0 && turn_direction == -1) || (prod < 0 && turn_direction == 1))) continue;

        va_end(p_args);
        *result = 0;
        return OK;
    }

    va_end(p_args);
    *result = 1;
    return OK;
}