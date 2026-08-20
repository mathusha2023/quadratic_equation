#include <stdio.h>
#include "get_coeffs.h"
#include "solve_equation.h"
#include "process_roots.h"

int main(void)
{
    float a = 0, b = 0, c = 0;

    get_coeffs_in_loop(&a, &b, &c, &get_coeffs);

    float x1 = 0, x2 = 0;

    int n_roots = solve_quadratic_equation(a, b, c, &x1, &x2);

    process_roots_with_print(n_roots, x1, x2);

    return 0;
}