#include "process_roots.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "solve_equation.h"
#include "config.h"
#include "strings.h"
#include "files.h"
#include "my_assert.h"

static double normilize_zero(double x)
{
    return fabs(x) < EPSILON ? 0.0 : x;
}

static const char *get_str_roots_count(enum RootsCount count)
{
    switch (count)
    {
    case INFINITY_ROOTS:
        return "бесконечно много";
    case NO_REAL_ROOTS:
        return "нет корней";
    case ONE_REAL_ROOT:
        return "1";
    case TWO_REAL_ROOTS:
        return "2";
    default:
        return "ошибка";
    }
}

void pretty_print_equation(struct QuadraticEquation *equation)
{
    my_assert(equation);

    if (!d_is_equal(equation->a, 0))
    {
        if (d_is_equal(equation->a, 1))
            ;
        else if (d_is_equal(equation->a, -1))
            printf("-");
        else
            printf("%lg", equation->a);

        printf("x^2");

        if (!d_is_equal(equation->b, 0)) // b != 0
        {
            printf(" %c ", equation->b > 0 ? '+' : '-');

            if (d_is_equal(fabs(equation->b), 1))
                ;
            else
                printf("%lg", fabs(equation->b));

            printf("x");
        }

        if (!d_is_equal(equation->c, 0))
        {
            printf(" %c ", equation->c > 0 ? '+' : '-');
            printf("%lg", fabs(equation->c));
        }
    }
    else // a = 0
    {
        if (!d_is_equal(equation->b, 0)) // a = 0, b != 0
        {
            if (d_is_equal(equation->b, 1))
                ;
            else if (d_is_equal(equation->b, -1))
                printf("-");
            else
                printf("%lg", equation->b);

            printf("x");

            if (!d_is_equal(equation->c, 0))
            {
                printf(" %c ", equation->c > 0 ? '+' : '-');
                printf("%lg", fabs(equation->c));
            }
        }
        else // a = 0, b = 0
        {
            printf("%lg", equation->c);
        }
    }

    printf(" = 0\n");
}

static int print_answer_table(struct QuadraticEquation *equation)
{
    my_assert(equation);

    printf("%s", GREEN_C);
    printf("Уравнение: ");
    pretty_print_equation(equation);
    printf("Число корней: %s\n", get_str_roots_count(equation->n_roots));
    printf("Корни: ");

    switch (equation->n_roots)
    {
    case INFINITY_ROOTS:
        printf("x ∈ ℝ\n");
        break;
    case NO_REAL_ROOTS:
        printf("∅\n");
        break;
    case ONE_REAL_ROOT:
        printf("x = %lg\n", normilize_zero(equation->x1));
        break;
    case TWO_REAL_ROOTS:
        printf("x1 = %lg, x2 = %lg\n", normilize_zero(equation->x1), normilize_zero(equation->x2));
        break;
    default:
        printf("Ошибка\n" RESET_C);
        return 0;
    }
    printf("%s", RESET_C);
    return 1;
}

static void loading(void)
{
    const int sleep_time = 4; // in seconds
    const int n_ticks = 100;

    printf("%s", YELLOW_C);
    for (int i = 0; i < n_ticks; i++)
    {
        printf("%sРешено %d%%\r", ARROW_S, i * n_ticks / 100);
        if (ARGS.output_delay)
        {
            fflush(stdout);
            usleep((int)1e6 * sleep_time / n_ticks); // microseconds
        }
    }
    printf("%sРешено 100%%\n", ARROW_S);
    printf(RESET_C);
}

void process_roots_with_pretty_print(struct QuadraticEquation *equation)
{
    my_assert(equation);

    print_phrase(THINKING_S);
    loading();
    print_phrase(SOLVED_S);
    printf("\n");
    print_answer_table(equation);
    printf(RESET_C);
}
