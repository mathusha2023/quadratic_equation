#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solve_equation.h"
#include "parser.h"
#include "config.h"

static const struct ParserTestCase test_cases[] = {
    {1, "2x^2 + 3x + 1 = 0", 1, 1, {2, 3, 1, 0, 0, NO_REAL_ROOTS}},
    {2, "x^2 + x + 1 = 0", 1, 1, {1, 1, 1, 0, 0, NO_REAL_ROOTS}},
    {3, "-x^2 - x - 1 = 0", 1, 1, {-1, -1, -1, 0, 0, NO_REAL_ROOTS}},
    {4, "5x^2 = 0", 1, 1, {5, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {5, "3x + 2 = 0", 1, 1, {0, 3, 2, 0, 0, NO_REAL_ROOTS}},
    {6, "7 = 0", 1, 1, {0, 0, 7, 0, 0, NO_REAL_ROOTS}},
    {7, "x^2 = 2x^2 + 3x + 4", 1, 1, {-1, -3, -4, 0, 0, NO_REAL_ROOTS}},
    {8, "2x^2 + 3x + 1 = 2x^2 + 3x + 1", 1, 1, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {9, "1.5x^2 + 2.7x + 3.9 = 0", 1, 1, {1.5, 2.7, 3.9, 0, 0, NO_REAL_ROOTS}},
    {10, "-2.5x^2 - 3.5x - 4.5 = 1.5x^2 + 2.5x + 3.5", 1, 1, {-4, -6, -8, 0, 0, NO_REAL_ROOTS}},
    {11, "x^2 + 1 = 2x^2 + 3", 1, 1, {-1, 0, -2, 0, 0, NO_REAL_ROOTS}},
    {12, "0x^2 + 0x + 0 = 0", 1, 1, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {13, "10x^2 - 20x + 30 = 5x^2 + 10x - 15", 1, 1, {5, -30, 45, 0, 0, NO_REAL_ROOTS}},
    {14, "x^2 = x^2", 1, 1, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {15, "x = x", 1, 1, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {16, "0 = 0", 1, 1, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {17, "2.5x^2 = 1.5x^2 + 2x + 3", 1, 1, {1, -2, -3, 0, 0, NO_REAL_ROOTS}},
    {18, "x^2 + 2x + 1 = x^2 + 2x + 1", 1, 1, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},

    {19, "2x^2 + 3x + 1", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {20, "2x^2 + 3x + 1 = 0 = 5", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {21, "2*x^2 + 3x + 1 = 0", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {22, "2x^2 + 3x + 1 = 0x", 1, 1, {2, 3, 1, 0, 0, NO_REAL_ROOTS}},
    {23, "2x^2 + 3x + 1 = ", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {24, "2x^2 + 3x + 1 = abc", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {25, "", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {26, "2x^3 + 3x + 1 = 0", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {27, "2x^2 + 3y + 1 = 0", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {28, "2x^ + 3x + 1 = 0", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {29, "2x^2 + + 3x + 1 = 0", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {30, "2x^2 + 3x + 1 = 0 +", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {31, "2x^2 3x + 1 = 0", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {32, "x^2.5 + 3x + 1 = 0", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {33, "2.5.7x^2 + 3x + 1 = 0", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {34, "2x^2 + 3x + 1 = 0 5", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {35, "x + x^2 + x^2 = 0", 1, 1, {2, 1, 0, 0, 0, NO_REAL_ROOTS}},
    {36, "2x^2 + 3x + 1 = 2x^2 +", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {37, "= 2x^2 + 3x + 1", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {38, "2x^2 + 3x + 1 == 0", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {39, "2x^2 + 3x + 1 = 0;", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {40, "2x^2 + 3x + 1 = 0\n", 1, 1, {2, 3, 1, 0, 0, NO_REAL_ROOTS}},
    {41, "x^2 = x^2 + x^2", 1, 1, {-1, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {42, "2x^2 + 3x + 1 = 2x^2 + 3x + 1 +", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {43, "2x^2 + 3x + 1 = 0 -", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {44, "2x^2 + 3x + 1 = 0 0", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {45, "x^2 + x^2 = 2x^2", 1, 1, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {46, " ", 0, 0, {0, 0, 0, 0, 0, NO_REAL_ROOTS}},
    {47, "2x^2 + 3x + 1 = 0 ", 1, 1, {2, 3, 1, 0, 0, NO_REAL_ROOTS}},
    {48, " 2x^2 + 3x + 1 = 0", 1, 1, {2, 3, 1, 0, 0, NO_REAL_ROOTS}},
    {49, "2x^2+3x+1=0", 1, 1, {2, 3, 1, 0, 0, NO_REAL_ROOTS}},
    {50, "2x^2 - 3x + 1 = x^2 + x - 2", 1, 1, {1, -4, 3, 0, 0, NO_REAL_ROOTS}},
};

static const char *get_success_str(int is_correct)
{
    return is_correct ? "successful parsing" : "failed parsing";
}

static int run_test(struct ParserTestCase test_case)
{
    char *s = (char *)calloc(strlen(test_case.s) + 1, sizeof(char));
    strcpy(s, test_case.s);
    struct Parser parser = init_parser(s);

    if (parser.is_correct_format != test_case.is_correct_format)
    {
        printf(RED_C "Parser test %d FAILED\n"
                     "String: %s\n"
                     "Expected: parser.is_correct_format=%d\n"
                     "Got:      parser.is_correct_format=%d\n" RESET_C,
               test_case.num, test_case.s, test_case.is_correct_format, parser.is_correct_format);
        free(s);
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
        free(s);
        return 0;
    }

    if (d_is_equal(eq.a, test_case.equation.a) && d_is_equal(eq.b, test_case.equation.b) && d_is_equal(eq.b, test_case.equation.b))
    {
        printf(GREEN_C "Parser test %d passed!\n" RESET_C, test_case.num);
        free(s);
        return 1;
    }
    printf(RED_C "Parser test %d FAILED\n"
                 "String: %s\n"
                 "Expected: a=%lg, b=%lg, c=%lg\n"
                 "Got:      a=%lg, b=%lg, c=%lg\n" RESET_C,
           test_case.num, test_case.s,
           test_case.equation.a, test_case.equation.b, test_case.equation.c,
           eq.a, eq.b, eq.c);
    free(s);
    return 0;
}

int run_parser_tests(void)
{
    int passed = 0;
    int test_count = sizeof test_cases / sizeof(struct ParserTestCase);

    printf("Start parser testing\n");

    for (int i = 0; i < test_count; i++)
        passed += run_test(test_cases[i]);

    int are_all_passed = passed == test_count;

    printf("End parser testing\n");
    printf("%sPassed: %d/%d tests\n\n%s",
           are_all_passed ? "\x1b[32m" : "\x1b[31m",
           passed, test_count,
           "\x1b[0m");

    return are_all_passed;
}