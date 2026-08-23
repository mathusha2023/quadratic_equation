#include "tests.h"
#include <stdio.h>
#include "solve_equation/tests.h"
#include "parser/tests.h"

int runTests(void)
{
    int res1 = run_equation_tests();
    int res2 = run_parser_tests();
    int are_all_passed = res1 && res2;
    if (are_all_passed)
        printf("\x1b[32mAll tests are passed!\x1b[0m");
    else
    {
        if (!res1)
            printf("\x1b[31mQuadratic equation tests are not passed\n\x1b[0m");
        if (!res2)
            printf("\x1b[31mParser tests are not passed\n\x1b[0m");
    }
    return are_all_passed;
}
