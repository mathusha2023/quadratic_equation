#include <stdio.h>
#include "get_coeffs.h"
#include "solve_equation.h"
#include "process_roots.h"
#include "cmd_args.h"
#include "tests/tests.h"

/// @brief Global variable of allowed cmd args
struct CmdArgs ARGS = {
    .colors = 1,
    .output_delay = 1,
    .speech = 1,
    .graph = 1,
    .ascii_arts = 1};

int main(int argc, char *argv[])
{
    get_args(argc, argv);

    if (ARGS.test)
        return !runTests();

    struct QuadraticEquation equation = {.n_roots = NO_REAL_ROOTS};

    if (ARGS.ascii_arts)
        print_logo();

    print_greeting();
    get_coeffs_in_loop(&equation);
    solve_quadratic_equation(&equation);
    process_roots_with_pretty_print(&equation);

    return 0;
}