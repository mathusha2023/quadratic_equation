#include "tests.h"
#include <stdio.h>
#include "config.h"
#include "solve_equation/tests.h"
// #include "parser/tests.h"
#include "fsm_parser/tests.h"

int runTests(void)
{
    int res1 = run_equation_tests();
    int res2 = run_fsm_parser_tests();
    int are_all_passed = res1 && res2;
    if (are_all_passed)
        printf(GREEN_COLOR "All tests are passed!\n" RESET_COLOR); // зеленый
    else
    {
        if (!res1)
            printf(RED_COLOR "Quadratic equation tests are not passed\n" RESET_COLOR); // красный
        if (!res2)
            printf(RED_COLOR "Parser tests are not passed\n" RESET_COLOR); // красный
    }
    return are_all_passed;
}
