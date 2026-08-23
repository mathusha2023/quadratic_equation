#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solve_equation.h"
#include "fsm_parser.h"
#include "config.h"

static const struct FSMParserTestCase test_cases[] = {
    {.num = 1,
     .s = "x^2+2x+1=0",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 2,
     .s = "x^2=0",
     .error_index = -1,
     .equation = {.a = 1}},
    {.num = 3,
     .s = "x^2+x=0",
     .error_index = -1,
     .equation = {.a = 1, .b = 1}},
    {.num = 4,
     .s = "x^2+1=0",
     .error_index = -1,
     .equation = {.a = 1, .c = 1}},
    {.num = 5,
     .s = "2x^2+3x+4=0",
     .error_index = -1,
     .equation = {.a = 2, .b = 3, .c = 4}},
    {.num = 6,
     .s = "-x^2+x-1=0",
     .error_index = -1,
     .equation = {.a = -1, .b = 1, .c = -1}},
    {.num = 7,
     .s = "x^2-2x+1=0",
     .error_index = -1,
     .equation = {.a = 1, .b = -2, .c = 1}},
    {.num = 8,
     .s = "3x^2-4x-5=0",
     .error_index = -1,
     .equation = {.a = 3, .b = -4, .c = -5}},
    {.num = 9,
     .s = "x^2+2x+1=x^2+2x+1",
     .error_index = -1,
     .equation = {.a = 0, .b = 0, .c = 0}},
    {.num = 10,
     .s = "x^2+1=2x^2+3x+4",
     .error_index = -1,
     .equation = {.a = -1, .b = -3, .c = -3}},
    {.num = 11,
     .s = "2x^2=0",
     .error_index = -1,
     .equation = {.a = 2}},
    {.num = 12,
     .s = "x^2+x+1=x^2-x-1",
     .error_index = -1,
     .equation = {.a = 0, .b = 2, .c = 2}},
    {.num = 13,
     .s = "0.5x^2+1.5x+2.5=0",
     .error_index = -1,
     .equation = {.a = 0.5, .b = 1.5, .c = 2.5}},
    {.num = 14,
     .s = "0.25x^2+0.75x+1.25=0",
     .error_index = -1,
     .equation = {.a = 0.25, .b = 0.75, .c = 1.25}},
    {.num = 15,
     .s = "-0.5x^2-1.25x+2.75=0",
     .error_index = -1,
     .equation = {.a = -0.5, .b = -1.25, .c = 2.75}},
    {.num = 16,
     .s = "1.0x^2+1.0x+1.0=0",
     .error_index = -1,
     .equation = {.a = 1.0, .b = 1.0, .c = 1.0}},
    {.num = 17,
     .s = "x^2+x+1=0",
     .error_index = -1,
     .equation = {.a = 1, .b = 1, .c = 1}},
    {.num = 18,
     .s = "x^2+0x+0=0",
     .error_index = -1,
     .equation = {.a = 1}},
    {.num = 19,
     .s = "0x^2+2x+1=0",
     .error_index = -1,
     .equation = {.b = 2, .c = 1}},
    {.num = 20,
     .s = "0x^2+0x+0=0",
     .error_index = -1,
     .equation = {}},
    {.num = 21,
     .s = "1x^2+1x+1=0",
     .error_index = -1,
     .equation = {.a = 1, .b = 1, .c = 1}},
    {.num = 22,
     .s = "-1x^2-1x-1=0",
     .error_index = -1,
     .equation = {.a = -1, .b = -1, .c = -1}},
    {.num = 23,
     .s = "10x^2+20x+30=5x^2+10x+15",
     .error_index = -1,
     .equation = {.a = 5, .b = 10, .c = 15}},
    {.num = 24,
     .s = "0=0",
     .error_index = -1,
     .equation = {}},
    {.num = 25,
     .s = "1=1",
     .error_index = -1,
     .equation = {}},
    {.num = 26,
     .s = "123.456x^2+789.012x+345.678=0",
     .error_index = -1,
     .equation = {.a = 123.456, .b = 789.012, .c = 345.678}},
    {.num = 27,
     .s = "999.999x^2+999.999x+999.999=0",
     .error_index = -1,
     .equation = {.a = 999.999, .b = 999.999, .c = 999.999}},
    {.num = 28,
     .s = "0.001x^2+0.001x+0.001=0",
     .error_index = -1,
     .equation = {.a = 0.001, .b = 0.001, .c = 0.001}},
    {.num = 29,
     .s = " x^2+2x+1=0",
     .error_index = 0},
    {.num = 30,
     .s = "x^2+2x+1=0 ",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 31,
     .s = "x^2 + 2x + 1 = 0",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 32,
     .s = "  x^2+2x+1=0",
     .error_index = 0},
    {.num = 33,
     .s = "x^2  +  2x  +  1  =  0",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 34,
     .s = "x^2+2x+1= 0",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 35,
     .s = "x^2+2x+1 =0",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 36,
     .s = ".5x^2+1.5x+2.5=0",
     .error_index = 0},
    {.num = 37,
     .s = "x^2+.25x+1.5=0",
     .error_index = 4},
    {.num = 38,
     .s = "x^2+1.5x+.75=0",
     .error_index = 9},
    {.num = 39,
     .s = ".x^2+2x+1=0",
     .error_index = 0},
    {.num = 40,
     .s = "x^2+2x+1=.",
     .error_index = 9},
    {.num = 41,
     .s = "x^2+2x+1=0.",
     .error_index = 11},
    {.num = 42,
     .s = "x^2+.x+1=0",
     .error_index = 4},
    {.num = 43,
     .s = "",
     .error_index = 0},
    {.num = 44,
     .s = "x^2+2x+1",
     .error_index = 8},
    {.num = 45,
     .s = "x^2+2x+1=",
     .error_index = 9},
    {.num = 46,
     .s = "=0",
     .error_index = 0},
    {.num = 47,
     .s = "x^2+",
     .error_index = 4},
    {.num = 48,
     .s = "x^2+2x+",
     .error_index = 7},
    {.num = 49,
     .s = "x^2+2x+1=0+",
     .error_index = 11},
    {.num = 50,
     .s = "+x^2+2x+1=0",
     .error_index = 0},
    {.num = 51,
     .s = "x^2+2x+1=+0",
     .error_index = 9},
    {.num = 52,
     .s = "x^2+2x+1=-",
     .error_index = 10},
    {.num = 53,
     .s = "x^2++2x+1=0",
     .error_index = 4},
    {.num = 54,
     .s = "x^2+2x++1=0",
     .error_index = 7},
    {.num = 55,
     .s = "x^2+2x+1==0",
     .error_index = 9},
    {.num = 56,
     .s = "x^2+2x+1=0=0",
     .error_index = 10},
    {.num = 57,
     .s = "xx^2+2x+1=0",
     .error_index = 1},
    {.num = 58,
     .s = "x^2x+2x+1=0",
     .error_index = 3},
    {.num = 59,
     .s = "x^2+xx+1=0",
     .error_index = 5},
    {.num = 60,
     .s = "x^2+2xx+1=0",
     .error_index = 6},
    {.num = 61,
     .s = "x^2+2x+x=0",
     .error_index = -1,
     .equation = {.a = 1, .b = 3}},
    {.num = 62,
     .s = "x^+2x+1=0",
     .error_index = 2},
    {.num = 63,
     .s = "x^2+2x+1=0x^2+2x+1",
     .error_index = -1,
     .equation = {.a = 1}},
    {.num = 64,
     .s = "x^2+2x+1=0x",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 65,
     .s = "2x^2+3x+4=5x^2+6x+7=0",
     .error_index = 19},
    {.num = 66,
     .s = "x^2+2x+1=abc",
     .error_index = 9},
    {.num = 67,
     .s = "abc=0",
     .error_index = 0},
    {.num = 68,
     .s = "x^2+2x+1=0x^2",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 69,
     .s = "1.2.3x^2+2x+1=0",
     .error_index = 3},
    {.num = 70,
     .s = "x^2+2.x+1=0",
     .error_index = 5},
    {.num = 71,
     .s = "x^2+2x+1.=0",
     .error_index = 8},
    {.num = 72,
     .s = "x^2+2x+1=1.2.3",
     .error_index = 12},
    {.num = 73,
     .s = "x^2+2x+1=x^2+2x+1+5",
     .error_index = -1,
     .equation = {.c = -5}},
    {.num = 74,
     .s = "5+x^2+2x+1=0",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 6}},
    {.num = 75,
     .s = "x^2+2x+1=5+0",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = -4}},
    {.num = 76,
     .s = "5=0",
     .error_index = -1,
     .equation = {.c = 5}},
    {.num = 77,
     .s = "5=x^2",
     .error_index = -1,
     .equation = {.a = -1, .c = 5}},
    {.num = 78,
     .s = "x^2+2x+1=5",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = -4}},
    {.num = 79,
     .s = "x^2+2x+1=0   ",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 80,
     .s = "x^2+2x+1=0\t",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 81,
     .s = "x^2+2x+1=0\n",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 82,
     .s = "x^2\t+\t2x\t+\t1\t=\t0",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 83,
     .s = "x^2\n+\n2x\n+\n1\n=\n0",
     .error_index = -1,
     .equation = {.a = 1, .b = 2, .c = 1}},
    {.num = 84,
     .s = "x^2 + 2x + 1 = x^2 + 2x + 1",
     .error_index = -1,
     .equation = {.a = 0, .b = 0, .c = 0}},
    {.num = 85,
     .s = "  x^2+2x+1=0  ",
     .error_index = 0},
};

static int run_test(struct FSMParserTestCase test_case)
{
    char *s = (char *)calloc(strlen(test_case.s) + 1, sizeof(char));
    strcpy(s, test_case.s);

    struct QuadraticEquation eq = {.n_roots = NO_REAL_ROOTS};
    struct FSMParser parser = init_fsmparser(s, &eq);

    char *c = parser.parse(&parser);

    if (c)
    {
        int ind = (int)(c - s);

        if (ind != test_case.error_index)
        {
            printf(RED_C "Parser test %d FAILED\n"
                         "String: %s\n"
                         "Expected: error_index=%d\n"
                         "Got:      error_index=%d\n" RESET_C,
                   test_case.num, test_case.s, test_case.error_index, ind);
            free(s);
            return 0;
        }

        printf(GREEN_C "Parser test %d passed!\n" RESET_C, test_case.num);
        free(s);
        return 1;
    }

    if (test_case.error_index != -1)
    {
        printf(RED_C "Parser test %d FAILED\n"
                     "String: %s\n"
                     "Expected: error_index=%d\n"
                     "Got:      error_index=-1\n" RESET_C,
               test_case.num, test_case.s, test_case.error_index);
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

int run_fsm_parser_tests(void)
{
    int passed = 0;
    int test_count = sizeof test_cases / sizeof(struct FSMParserTestCase);

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