#include <stdio.h>
#include "get_coeffs.h"
#include "solve_equation.h"
#include "process_roots.h"
#include "cmd_args.h"
#include "tests/tests.h"

struct CmdArgs ARGS = {.colors = 1};

int main(int argc, char *argv[])
{
    get_args(argc, argv);

    if (ARGS.test)
        return !runTests();

    struct QuadraticEquation equation = {.n_roots = NO_REAL_ROOTS};

    get_coeffs_in_loop(&equation, &parse_coeffs_from_equation);
    solve_quadratic_equation(&equation);
    process_roots_with_print(&equation);

    return 0;
}