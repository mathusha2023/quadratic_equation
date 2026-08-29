#include "tests.h"
#include <stdio.h>
#include "solve_equation.h"
#include "config.h"
#include "my_assert.h"

static const struct EquationTestCase test_cases[] = {
    {.num = 1,
     .equation = {.a = 1,
                  .b = -5,
                  .c = 6,
                  .x1 = 3,
                  .x2 = 2,
                  .n_roots = TWO_REAL_ROOTS}}, // x^2 - 5x + 6 = 0
    {.num = 2,
     .equation = {.a = 1,
                  .b = -3,
                  .c = 2,
                  .x1 = 2,
                  .x2 = 1,
                  .n_roots = TWO_REAL_ROOTS}}, // x^2 - 3x + 2 = 0
    {.num = 3,
     .equation = {.a = 2,
                  .b = -7,
                  .c = 3,
                  .x1 = 3,
                  .x2 = 0.5,
                  .n_roots = TWO_REAL_ROOTS}}, // 2x^2 - 7x + 3 = 0
    {.num = 4,
     .equation = {.a = 1,
                  .b = 0,
                  .c = -1,
                  .x1 = 1,
                  .x2 = -1,
                  .n_roots = TWO_REAL_ROOTS}}, // x^2 - 1 = 0
    {.num = 5,
     .equation = {.a = 4,
                  .b = -4,
                  .c = -3,
                  .x1 = 1.5,
                  .x2 = -0.5,
                  .n_roots = TWO_REAL_ROOTS}}, // 4x^2 - 4x - 3 = 0

    {.num = 6,
     .equation = {.a = 1,
                  .b = -4,
                  .c = 4,
                  .x1 = 2,
                  .x2 = 2,
                  .n_roots = ONE_REAL_ROOT}}, // x^2 - 4x + 4 = 0
    {.num = 7,
     .equation = {.a = 1,
                  .b = 2,
                  .c = 1,
                  .x1 = -1,
                  .x2 = -1,
                  .n_roots = ONE_REAL_ROOT}}, // x^2 + 2x + 1 = 0
    {.num = 8,
     .equation = {.a = 4,
                  .b = -4,
                  .c = 1,
                  .x1 = 0.5,
                  .x2 = 0.5,
                  .n_roots = ONE_REAL_ROOT}}, // 4x^2 - 4x + 1 = 0
    {.num = 9,
     .equation = {.a = 1,
                  .b = 0,
                  .c = 0,
                  .x1 = 0,
                  .x2 = 0,
                  .n_roots = ONE_REAL_ROOT}}, // x^2 = 0

    {.num = 10,
     .equation = {.a = 1,
                  .b = 0,
                  .c = 1,
                  .x1 = 0,
                  .x2 = 0,
                  .n_roots = NO_REAL_ROOTS}}, // x^2 + 1 = 0
    {.num = 11,
     .equation = {.a = 1,
                  .b = -2,
                  .c = 3,
                  .x1 = 0,
                  .x2 = 0,
                  .n_roots = NO_REAL_ROOTS}}, // x^2 - 2x + 3 = 0
    {.num = 12,
     .equation = {.a = 2,
                  .b = 1,
                  .c = 5,
                  .x1 = 0,
                  .x2 = 0,
                  .n_roots = NO_REAL_ROOTS}}, // 2x^2 + x + 5 = 0
    {.num = 13,
     .equation = {.a = 1,
                  .b = -1,
                  .c = 1,
                  .x1 = 0,
                  .x2 = 0,
                  .n_roots = NO_REAL_ROOTS}}, // x^2 - x + 1 = 0

    {.num = 14,
     .equation = {.a = -1,
                  .b = 5,
                  .c = -6,
                  .x1 = 3,
                  .x2 = 2,
                  .n_roots = TWO_REAL_ROOTS}}, // -x^2 + 5x - 6 = 0
    {.num = 15,
     .equation = {.a = -1,
                  .b = -2,
                  .c = -1,
                  .x1 = -1,
                  .x2 = -1,
                  .n_roots = ONE_REAL_ROOT}}, // -x^2 - 2x - 1 = 0
    {.num = 16,
     .equation = {.a = -1,
                  .b = 0,
                  .c = -1,
                  .x1 = 0,
                  .x2 = 0,
                  .n_roots = NO_REAL_ROOTS}}, // -x^2 - 1 = 0

    {.num = 17,
     .equation = {.a = 0.5,
                  .b = -1,
                  .c = 0.5,
                  .x1 = 1,
                  .x2 = 1,
                  .n_roots = ONE_REAL_ROOT}}, // 0.5x^2 - x + 0.5 = 0
    {.num = 18,
     .equation = {.a = 0.25,
                  .b = -1,
                  .c = 1,
                  .x1 = 2,
                  .x2 = 2,
                  .n_roots = ONE_REAL_ROOT}}, // 0.25x^2 - x + 1 = 0

    {.num = 19,
     .equation = {.a = 0,
                  .b = 2,
                  .c = -4,
                  .x1 = 2,
                  .x2 = 2,
                  .n_roots = ONE_REAL_ROOT}}, // 2x - 4 = 0
    {.num = 20,
     .equation = {.a = 0,
                  .b = 3,
                  .c = 9,
                  .x1 = -3,
                  .x2 = -3,
                  .n_roots = ONE_REAL_ROOT}}, // 3x + 9 = 0
    {.num = 21,
     .equation = {.a = 0,
                  .b = -5,
                  .c = 10,
                  .x1 = 2,
                  .x2 = 2,
                  .n_roots = ONE_REAL_ROOT}}, // -5x + 10 = 0
    {.num = 22,
     .equation = {.a = 0,
                  .b = 1,
                  .c = -0.5,
                  .x1 = 0.5,
                  .x2 = 0.5,
                  .n_roots = ONE_REAL_ROOT}}, // x - 0.5 = 0

    {.num = 23,
     .equation = {.a = 0,
                  .b = -2,
                  .c = -6,
                  .x1 = -3,
                  .x2 = -3,
                  .n_roots = ONE_REAL_ROOT}}, // -2x - 6 = 0

    {.num = 24,
     .equation = {.a = 0,
                  .b = 4,
                  .c = -2,
                  .x1 = 0.5,
                  .x2 = 0.5,
                  .n_roots = ONE_REAL_ROOT}}, // 4x - 2 = 0
    {.num = 25,
     .equation = {.a = 0,
                  .b = 2,
                  .c = 1,
                  .x1 = -0.5,
                  .x2 = -0.5,
                  .n_roots = ONE_REAL_ROOT}}, // 2x + 1 = 0

    {.num = 26,
     .equation = {.a = 0,
                  .b = 0,
                  .c = 0,
                  .x1 = 0,
                  .x2 = 0,
                  .n_roots = INFINITY_ROOTS}},

    {.num = 27,
     .equation = {.a = 0,
                  .b = 0,
                  .c = 1,
                  .x1 = 0,
                  .x2 = 0,
                  .n_roots = NO_REAL_ROOTS}},
    {.num = 28,
     .equation = {.a = 0,
                  .b = 0,
                  .c = -5,
                  .x1 = 0,
                  .x2 = 0,
                  .n_roots = NO_REAL_ROOTS}},

    {.num = 29,
     .equation = {.a = 1,
                  .b = -1,
                  .c = -1,
                  .x1 = 1.618033988749895,
                  .x2 = -0.618033988749895,
                  .n_roots = TWO_REAL_ROOTS}},
    {.num = 30,
     .equation = {.a = 1,
                  .b = 1,
                  .c = -1,
                  .x1 = 0.618033988749895,
                  .x2 = -1.618033988749895,
                  .n_roots = TWO_REAL_ROOTS}},

    {.num = 31,
     .equation = {.a = 1,
                  .b = -1000000000,
                  .c = 1,
                  .x1 = 1000000000,
                  .x2 = 1e-9,
                  .n_roots = TWO_REAL_ROOTS}},
    {.num = 32,
     .equation = {.a = 1,
                  .b = 1000000000,
                  .c = 1,
                  .x1 = -1e-9,
                  .x2 = -1000000000,
                  .n_roots = TWO_REAL_ROOTS}},

    {.num = 33,
     .equation = {.a = 0,
                  .b = 1,
                  .c = -1,
                  .x1 = 1,
                  .x2 = 1,
                  .n_roots = ONE_REAL_ROOT}}, // x - 1 = 0
    {.num = 34,
     .equation = {.a = 0,
                  .b = -1,
                  .c = -1,
                  .x1 = -1,
                  .x2 = -1,
                  .n_roots = ONE_REAL_ROOT}}, // -x - 1 = 0
    {.num = 35,
     .equation = {.a = 0,
                  .b = 0.000001,
                  .c = -0.000002,
                  .x1 = 2,
                  .x2 = 2,
                  .n_roots = ONE_REAL_ROOT}},
};

/**
 * @brief Check if equations answers are equal
 *
 * @param eq1
 * @param eq2
 * @return int 1 if equations are equal else 0
 */
static int check_equal(struct QuadraticEquation *eq1, struct QuadraticEquation *eq2)
{
    my_assert(eq1);
    my_assert(eq2);
    my_assert(eq1 != eq2);
    my_assert(isfinite(eq1->x1));
    my_assert(isfinite(eq1->x2));
    my_assert(isfinite(eq2->x1));
    my_assert(isfinite(eq2->x2));

    return eq1->n_roots == eq2->n_roots &&
           ((d_is_equal(eq1->x1, eq2->x1) && d_is_equal(eq1->x2, eq2->x2)) ||
            (d_is_equal(eq1->x1, eq2->x2) && d_is_equal(eq1->x2, eq2->x1)));
}

/**
 * @brief Get the roots count str object
 *
 * @param n_roots
 * @return const char*
 */
static const char *get_roots_count_str(enum RootsCount n_roots)
{
    switch (n_roots)
    {
    case INFINITY_ROOTS:
        return "INFINITY_ROOTS";
    case NO_REAL_ROOTS:
        return "NO_REAL_ROOTS";
    case ONE_REAL_ROOT:
        return "ONE_REAL_ROOT";
    case TWO_REAL_ROOTS:
        return "TWO_REAL_ROOTS";
    default:
        return "UNKNOWN";
    }
}

/**
 * @brief Run one equations solver test
 *
 * @param test_case
 * @return int 1 if passed else 0
 */
static int run_test(struct EquationTestCase test_case)
{
    struct QuadraticEquation equation = {.a = test_case.equation.a,
                                         .b = test_case.equation.b,
                                         .c = test_case.equation.c,
                                         .n_roots = NO_REAL_ROOTS};
    solve_quadratic_equation(&equation);

    int is_passed = check_equal(&equation, &test_case.equation);
    if (is_passed)
    {
        printf("%sQuadratic equation test %d passed!\n%s", GREEN_C, test_case.num, RESET_C);
    }
    else
    {
        printf("%sQuadratic equation test %d FAILED\n"
               "Expected %s roots, x1=%lg, x2=%lg\n"
               "Got      %s roots, x1=%lg, x2=%lg\n%s",
               RED_C,
               test_case.num,
               get_roots_count_str(test_case.equation.n_roots),
               test_case.equation.x1, test_case.equation.x2,
               get_roots_count_str(equation.n_roots),
               equation.x1, equation.x2, RESET_C);
    }
    return is_passed;
}

int run_equation_tests(void)
{
    int passed = 0;
    int test_count = sizeof test_cases / sizeof(struct EquationTestCase);

    printf("Start quadratic equations testing\n");

    for (int i = 0; i < test_count; i++)
        passed += run_test(test_cases[i]);

    int are_all_passed = passed == test_count;

    printf("End quadratic equations testing\n");
    printf("%sPassed: %d/%d tests\n\n%s",
           are_all_passed ? GREEN_COLOR : RED_COLOR,
           passed, test_count,
           RESET_COLOR);

    return are_all_passed;
}