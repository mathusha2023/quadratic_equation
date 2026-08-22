#include "tests.h"
#include <stdio.h>
#include "solve_equation.h"
#include "parser.h"
#include "config.h"

static const struct ParserTestCase test_cases[] = {};

static const char *get_success_str(int is_correct)
{
    return is_correct ? "successful parsing" : "failed parsing";
}

static int run_test(struct ParserTestCase test_case)
{
    struct Parser parser = init_parser(test_case.s);

    if (parser.is_correct_format != test_case.is_correct_format)
    {
        printf(RED_C "Parser test %d FAILED\n"
                     "String: %s\n"
                     "Expected: parser.is_correct_format=%d\n"
                     "Got:      parser.is_correct_format=%d\n" RESET_C,
               test_case.num, test_case.s, test_case.is_correct_format, parser.is_correct_format);
        return 0;
    }

    struct QuadraticEquation eq = {0, 0, 0, 0, 0, NO_REAL_ROOTS};
    int is_correct_parse = parser.parse(&parser, &eq);

    if (is_correct_parse != test_case.is_correct_parse)
    {
        printf(RED_C "Parser test %d FAILED\n"
                     "String: %s\n"
                     "Expected: %s\n"
                     "Got:      %s\n" RESET_C,
               test_case.num, test_case.s,
               get_success_str(test_case.is_correct_parse),
               get_success_str(is_correct_parse));
        return 0;
    }

    if (d_is_equal(eq.a, test_case.equation.a) && d_is_equal(eq.b, test_case.equation.b) && d_is_equal(eq.b, test_case.equation.b))
    {
        printf(GREEN_C "Parser test %d passed!\n" RESET_C, test_case.num);
        return 1;
    }
    printf(RED_C "Parser test %d FAILED\n"
                 "String: %s\n"
                 "Expected: a=%lg, b=%lg, c=%lg\n"
                 "Got:      a=%lg, b=%lg, c=%lg\n" RESET_C,
           test_case.num, test_case.s,
           test_case.equation.a, test_case.equation.b, test_case.equation.c,
           eq.a, eq.b, eq.c);
    return 0;
}

int run_parser_tests(void)
{
    int passed = 0;
    int test_count = sizeof test_cases / sizeof(struct ParserTestCase);

    for (int i = 0; i < test_count; i++)
        passed += run_test(test_cases[i]);

    int are_all_passed = passed == test_count;

    printf("End parser testing\n");
    printf("%sPassed: %d/%d tests\n%s",
           are_all_passed ? "\x1b[32m" : "\x1b[31m",
           passed, test_count,
           "\x1b[0m");

    return are_all_passed;
}