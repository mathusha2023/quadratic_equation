#include <stdio.h>
#include "get_coeffs.h"
#include "solve_equation.h"
#include "process_roots.h"

int main(void)
{
    struct QuadraticEquation equation = {0, 0, 0, 0, 0, NO_REAL_ROOTS};

    get_coeffs_in_loop(&equation, &parse_coeffs_from_equation);
    solve_quadratic_equation(&equation);
    process_roots_with_print(&equation);

    return 0;
}