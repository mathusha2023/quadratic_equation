#include "tests.h"
#include "solve_equation/tests.h"
#include "parser/tests.h"

int runTests(void)
{
    int res1 = run_equation_tests();
    int res2 = run_parser_tests();
    return res1 && res2;
}
