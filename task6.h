#include <math.h>
#include <stdarg.h>

int polynomial_value(double* const result, double const point, int const power, ...);

int task_6() {
    double result;
    int result_code = polynomial_value(&result, 2.3, 4, 5.3, 4.29, 42.42, 52.52, 81.84);
    switch (result_code) {
        case OK:
            printf("Result: %f", result);
            return OK;
        default:
            PRINT_ERROR_MESSAGE();
            return ERR;
    }
}

int polynomial_value(double* const result, double const point, int const power, ...) {
    va_list p_args;
    va_start(p_args, power);

    double coefficient;
    double value = 0.0;
    for(int i = power; i >= 0; i--) {
        coefficient = va_arg(p_args, double);
        value += coefficient * pow(point, i);
    }
    va_end(p_args);
    *result = value;
    return OK;
}