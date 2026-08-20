#include <stdio.h>
#include "solve_equation.h"
#include "process_roots.h"

void process_roots_with_print(struct QuadraticEquation *equation)
{
    switch (equation->n_roots)
    {
    case INFINITY_ROOTS:
        printf("Any number is solution\n");
        break;
    case NO_REAL_ROOTS:
        printf("No solutions\n");
        break;
    case ONE_REAL_ROOT:
        printf("x = %f\n", equation->x1);
        break;
    case TWO_REAL_ROOTS:
        printf("x1 = %f, x2 = %f\n", equation->x1, equation->x2);
        break;
    default:
        printf("Error:(\n");
        break;
    }
}