#include "tests.h"
#include <stdio.h>
#include "solve_equation.h"
#include "config.h"

static const struct EquationTestCase test_cases[] = {
    // Тесты для квадратных уравнений (a != 0)

    // Два различных вещественных корня
    {1, {1, -5, 6, 3, 2, TWO_REAL_ROOTS}},       // x^2 - 5x + 6 = 0
    {2, {1, -3, 2, 2, 1, TWO_REAL_ROOTS}},       // x^2 - 3x + 2 = 0
    {3, {2, -7, 3, 3, 0.5, TWO_REAL_ROOTS}},     // 2x^2 - 7x + 3 = 0
    {4, {1, 0, -1, 1, -1, TWO_REAL_ROOTS}},      // x^2 - 1 = 0
    {5, {4, -4, -3, 1.5, -0.5, TWO_REAL_ROOTS}}, // 4x^2 - 4x - 3 = 0

    // Один вещественный корень (дискриминант = 0)
    {6, {1, -4, 4, 2, 2, ONE_REAL_ROOT}},     // x^2 - 4x + 4 = 0
    {7, {1, 2, 1, -1, -1, ONE_REAL_ROOT}},    // x^2 + 2x + 1 = 0
    {8, {4, -4, 1, 0.5, 0.5, ONE_REAL_ROOT}}, // 4x^2 - 4x + 1 = 0
    {9, {1, 0, 0, 0, 0, ONE_REAL_ROOT}},      // x^2 = 0

    // Нет вещественных корней (дискриминант < 0)
    {10, {1, 0, 1, 0, 0, NO_REAL_ROOTS}},  // x^2 + 1 = 0
    {11, {1, -2, 3, 0, 0, NO_REAL_ROOTS}}, // x^2 - 2x + 3 = 0
    {12, {2, 1, 5, 0, 0, NO_REAL_ROOTS}},  // 2x^2 + x + 5 = 0
    {13, {1, -1, 1, 0, 0, NO_REAL_ROOTS}}, // x^2 - x + 1 = 0

    // Отрицательный коэффициент a
    {14, {-1, 5, -6, 3, 2, TWO_REAL_ROOTS}},   // -x^2 + 5x - 6 = 0
    {15, {-1, -2, -1, -1, -1, ONE_REAL_ROOT}}, // -x^2 - 2x - 1 = 0
    {16, {-1, 0, -1, 0, 0, NO_REAL_ROOTS}},    // -x^2 - 1 = 0

    // Дробные коэффициенты
    {17, {0.5, -1, 0.5, 1, 1, ONE_REAL_ROOT}}, // 0.5x^2 - x + 0.5 = 0
    {18, {0.25, -1, 1, 2, 2, ONE_REAL_ROOT}},  // 0.25x^2 - x + 1 = 0

    // Тесты для линейных уравнений (a = 0)

    // Обычное линейное уравнение
    {19, {0, 2, -4, 2, 2, ONE_REAL_ROOT}},       // 2x - 4 = 0
    {20, {0, 3, 9, -3, -3, ONE_REAL_ROOT}},      // 3x + 9 = 0
    {21, {0, -5, 10, 2, 2, ONE_REAL_ROOT}},      // -5x + 10 = 0
    {22, {0, 1, -0.5, 0.5, 0.5, ONE_REAL_ROOT}}, // x - 0.5 = 0

    // Линейное уравнение с отрицательным корнем
    {23, {0, -2, -6, -3, -3, ONE_REAL_ROOT}}, // -2x - 6 = 0

    // Линейное уравнение с дробным корнем
    {24, {0, 4, -2, 0.5, 0.5, ONE_REAL_ROOT}},  // 4x - 2 = 0
    {25, {0, 2, 1, -0.5, -0.5, ONE_REAL_ROOT}}, // 2x + 1 = 0

    // Вырожденные случаи (a = 0, b = 0)

    // Бесконечное множество решений (0 = 0)
    {26, {0, 0, 0, 0, 0, INFINITY_ROOTS}},

    // Нет решений (0 = c, где c != 0)
    {27, {0, 0, 1, 0, 0, NO_REAL_ROOTS}},
    {28, {0, 0, -5, 0, 0, NO_REAL_ROOTS}},

    // Смешанные тесты с положительными и отрицательными коэффициентами
    {40, {1, -1, -1, 1.618033988749895, -0.618033988749895, TWO_REAL_ROOTS}}, // Золотое сечение
    {41, {1, 1, -1, 0.618033988749895, -1.618033988749895, TWO_REAL_ROOTS}},

    // Тесты для проверки устойчивости алгоритма
    {42, {1, -1000000000, 1, 1000000000, 1e-9, TWO_REAL_ROOTS}},
    {43, {1, 1000000000, 1, -1e-9, -1000000000, TWO_REAL_ROOTS}},

    // Дополнительные вырожденные случаи
    {44, {0, 1, -1, 1, 1, ONE_REAL_ROOT}},               // x - 1 = 0
    {45, {0, -1, -1, -1, -1, ONE_REAL_ROOT}},            // -x - 1 = 0
    {46, {0, 0.000001, -0.000002, 2, 2, ONE_REAL_ROOT}}, // Очень маленькие коэффициенты
};

static int check_equal(struct QuadraticEquation *eq1, struct QuadraticEquation *eq2)
{
    return eq1->n_roots == eq2->n_roots && ((d_is_equal(eq1->x1, eq2->x1) && d_is_equal(eq1->x2, eq2->x2)) || (d_is_equal(eq1->x1, eq2->x2) && d_is_equal(eq1->x2, eq2->x1)));
}

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

static int run_test(struct EquationTestCase test_case)
{
    struct QuadraticEquation equation = {test_case.equation.a, test_case.equation.b, test_case.equation.c, 0, 0, NO_REAL_ROOTS};
    solve_quadratic_equation(&equation);

    int is_passed = check_equal(&equation, &test_case.equation);
    if (is_passed)
    {
        printf(GREEN_C "Quadratic equation test %d passed!\n" RESET_C, test_case.num);
    }
    else
    {
        printf(RED_C "Quadratic equation test %d FAILED\n"
                     "Expected %s roots, x1=%lg, x2=%lg\n"
                     "Got      %s roots, x1=%lg, x2=%lg\n" RESET_C,
               test_case.num,
               get_roots_count_str(test_case.equation.n_roots),
               test_case.equation.x1, test_case.equation.x2,
               get_roots_count_str(equation.n_roots),
               equation.x1, equation.x2);
    }
    return is_passed;
}

int run_equation_tests(void)
{
    int passed = 0;
    int test_count = sizeof test_cases / sizeof(struct EquationTestCase);

    for (int i = 0; i < test_count; i++)
        passed += run_test(test_cases[i]);

    int are_all_passed = passed == test_count;

    printf("End quadratic equations testing\n");
    printf("%sPassed: %d/%d tests\n%s",
           are_all_passed ? "\x1b[32m" : "\x1b[31m",
           passed, test_count,
           "\x1b[0m");

    return are_all_passed;
}