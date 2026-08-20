#ifndef SOLVE_EQUATION_H

#define SOLVE_EQUATION_H

enum roots_count
{
    INFINITY_ROOTS = -1,
    NO_REAL_ROOTS = 0,
    ONE_REAL_ROOT = 1,
    TWO_REAL_ROOTS = 2
};

int is_equal(float a, float b);
enum roots_count solve_quadratic_equation(float a, float b, float c, float *px1, float *px2);
enum roots_count solve_linear_equation(float b, float c, float *px);

#endif