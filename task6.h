#include <math.h>
#include <stdarg.h>

int polynomial_value(double* const result, double const point, int const power, ...);

int task_6(int argc, char** argv) {
    double result;
    int result_code = polynomial_value(&result, 2.0, 3, 3.0, 2.0, 1.0, 1.0);
    switch (result_code) {
        case OK:
            printf("Result: %f", result);
            break;
        case INVALID_PARAMETER:
            PRINT_INVALID_PARAMETER_MESSAGE();
            break;
        default:
            PRINT_ERROR_MESSAGE();
            break;
    }
    return result_code;
}

int polynomial_value(double * const result, double const point, int const power, ...) {
    if (result == NULL) return INVALID_PARAMETER;

    int i;
    double value = 0.0;
    va_list p_args;

    va_start(p_args, power);
    for (i = 0; i < power; i++) {
        value = value * point + va_arg(p_args, double);
    }
    va_end(p_args);

    *result = value;

    return OK;
}