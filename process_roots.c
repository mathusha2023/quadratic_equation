#include "process_roots.h"
#include <stdio.h>
#include <math.h>
#include "solve_equation.h"
#include "config.h"

static float normilize_zero(float x)
{
    return fabs(x) < 1e-8 ? 0.0 : x;
}

void process_roots_with_print(struct QuadraticEquation *equation)
{
    printf(GREEN_C);
    switch (equation->n_roots)
    {
    case INFINITY_ROOTS:
        printf("Any number is solution\n");
        break;
    case NO_REAL_ROOTS:
        printf("No solutions\n");
        break;
    case ONE_REAL_ROOT:
        printf("x = %f\n", normilize_zero(equation->x1));
        break;
    case TWO_REAL_ROOTS:
        printf("x1 = %f, x2 = %f\n", normilize_zero(equation->x1), normilize_zero(equation->x2));
        break;
    default:
        printf("Error:(\n");
        break;
    }
    printf(RESET_C);
}