#include <stdio.h>
#include "solve_equation.h"
#include "process_roots.h"

void process_roots_with_print(int n_roots, float x1, float x2)
{
    switch (n_roots)
    {
    case INFINITY_ROOTS:
        printf("Any number is solution\n");
        break;
    case 0:
        printf("No solutions\n");
        break;
    case 1:
        printf("x = %f\n", x1);
        break;
    case 2:
        printf("x1 = %f, x2 = %f\n", x1, x2);
        break;
    default:
        printf("Error:(\n");
        break;
    }
}