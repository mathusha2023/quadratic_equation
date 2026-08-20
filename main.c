#include <stdio.h>
#include "get_coeffs.h"
#include "solve_equation.h"

int main(void)
{
    float a = 0, b = 0, c = 0;

    if (!get_coeffs(&a, &b, &c))
    {
        printf("Enter correct coefficients!\n");
        return 1;
    }

    float x1 = 0, x2 = 0;

    int n_roots = solve_quadratic_equation(a, b, c, &x1, &x2);

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

    return 0;
}