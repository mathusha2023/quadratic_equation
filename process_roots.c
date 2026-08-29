#include "process_roots.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdarg.h>
#include "solve_equation.h"
#include "config.h"
#include "phrases.h"
#include "files.h"
#include "my_assert.h"
#include "graph.h"

/**
 * @brief Normilize zero
 *
 * If the number is close to zero, then it will be replaced with 0
 * It makes because double type has a limited precision
 *
 * @param x
 * @return double
 */
static double normilize_zero(double x)
{
    return fabs(x) < EPSILON ? 0.0 : x;
}

/**
 * @brief Get the str roots count object
 *
 * @param count
 * @return const char*
 */
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

/**
 * @brief Add formated string in the end of another string
 *
 * This function works like sprintf and save buffer from overflow
 *
 * @param [out]s in this string will be added formatted string
 * @param s_size size of allowed s space
 * @param [in]symb formatted string will be added to s
 * @param ... additional arguments
 * @return int 1 if successfully added else 0
 */
static int add_symb_to_str(char **s, size_t *s_size, const char *symb, ...)
{
    my_assert(s);
    my_assert(*s);
    my_assert(s_size);
    my_assert(symb);

    va_list args = {};
    va_start(args, symb);
    int res = vsnprintf(*s, *s_size, symb, args);
    va_end(args);

    my_assert(res > 0 && (size_t)res < *s_size);

    if (res < 0 || (size_t)res > *s_size)
        return 0;
    *s_size -= (size_t)res;
    *s += res;
    return 1;
}

/**
 * @brief Make string with equation in base format
 *
 * This function make string with equation in base format (ax^2 + bx + c = 0)
 * For example:
 * -x^2 + 2x + 3 = 0
 * x^2 - 2x = 0
 *
 * @param [out]s
 * @param equation
 * @param s_size
 * @return int
 */
static int make_pretty_eq(char *s, struct QuadraticEquation *equation, size_t s_size)
{
    my_assert(s);
    my_assert(equation);

    if (!d_is_equal(equation->a, 0))
    {
        if (d_is_equal(equation->a, 1))
            ;
        else if (d_is_equal(equation->a, -1))
        {
            if (!add_symb_to_str(&s, &s_size, "-"))
                return 0;
        }
        else
        {
            if (!add_symb_to_str(&s, &s_size, "%lg", equation->a))
                return 0;
        }

        if (!add_symb_to_str(&s, &s_size, "x^2"))
            return 0;

        if (!d_is_equal(equation->b, 0)) // b != 0
        {
            if (!add_symb_to_str(&s, &s_size, " %c ", equation->b > 0 ? '+' : '-'))
                return 0;

            if (d_is_equal(fabs(equation->b), 1))
                ;
            else
            {
                if (!add_symb_to_str(&s, &s_size, "%lg", fabs(equation->b)))
                    return 0;
            }

            if (!add_symb_to_str(&s, &s_size, "x"))
                ;
        }

        if (!d_is_equal(equation->c, 0))
        {
            if (!add_symb_to_str(&s, &s_size, " %c %lg", equation->c > 0 ? '+' : '-', fabs(equation->c)))
                return 0;
        }
    }
    else // a = 0
    {
        if (!d_is_equal(equation->b, 0)) // a = 0, b != 0
        {
            if (d_is_equal(equation->b, 1))
                ;
            else if (d_is_equal(equation->b, -1))
            {
                if (!add_symb_to_str(&s, &s_size, "-"))
                    return 0;
            }
            else
            {
                if (!add_symb_to_str(&s, &s_size, "%lg", equation->b))
                    return 0;
            }

            if (!add_symb_to_str(&s, &s_size, "x"))
                return 0;

            if (!d_is_equal(equation->c, 0))
            {
                if (!add_symb_to_str(&s, &s_size, " %c %lg", equation->c > 0 ? '+' : '-', fabs(equation->c)))
                    return 0;
            }
        }
        else // a = 0, b = 0
        {
            if (!add_symb_to_str(&s, &s_size, "%lg", equation->c))
                return 0;
        }
    }

    if (!add_symb_to_str(&s, &s_size, " = 0\n"))
        return 0;

    return 1;
}
/**
 * @brief Print equation in base format
 *
 * This function print the result of make_pretty_eq()
 *
 * @param equation
 */
static void pretty_print_equation(struct QuadraticEquation *equation)
{
    my_assert(equation);

    char *s = (char *)calloc(BUFFERSIZE, sizeof(char));
    if (!s)
    {
        printf("%sMemory ERROR!!!!\n%s", RED_C, RESET_C);
        return;
    }
    make_pretty_eq(s, equation, BUFFERSIZE);
    printf("%s", s);
    free(s);
}

/**
 * @brief Print all information about equation and roots for user
 *
 * @param equation
 * @return int 1 - success, 0 - error
 */
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
        printf("Ошибка\n%s", RESET_C);
        return 0;
    }
    printf("%s", RESET_C);
    return 1;
}

/**
 * @brief Print loading animation
 *
 * @note If ARGS.output_delay = 0 this function will print all data without delay
 *
 */
static void loading(void)
{
    const int sleep_time = 4; // in seconds
    const int n_ticks = 100;
    int j = 0;

    printf("%s", YELLOW_C);
    for (int i = 0; i <= n_ticks; i++)
    {
        printf("%sДумаю... ", ARROW_S);
        for (j = 0; j < 10; j++)
        {
            printf("%s", j * 10 < i ? "█" : "░");
        }
        printf(" %d%%\r", i);

        if (ARGS.output_delay)
        {
            fflush(stdout);
            usleep((int)1e6 * sleep_time / n_ticks); // microseconds
        }
    }
    printf("\n%s", RESET_C);
}

/**
 * @brief Print equation in console using ascii art
 *
 * @note This function need files with ascii arts
 *
 * @param equation
 */
static void print_equation_in_ascii_art(struct QuadraticEquation *equation)
{
    my_assert(equation);

    char *s = (char *)calloc(BUFFERSIZE, sizeof(char));
    if (!s)
    {
        printf("%sMemory ERROR!!!!\n%s", RED_C, RESET_C);
        return;
    }
    make_pretty_eq(s, equation, BUFFERSIZE);
    const int files_length = 5;

    static const char *file_names[256] = {['0'] = N0_F,
                                          ['1'] = N1_F,
                                          ['2'] = N2_F,
                                          ['3'] = N3_F,
                                          ['4'] = N4_F,
                                          ['5'] = N5_F,
                                          ['6'] = N6_F,
                                          ['7'] = N7_F,
                                          ['8'] = N8_F,
                                          ['9'] = N9_F,
                                          ['.'] = DOT_F,
                                          ['-'] = SUB_F,
                                          ['+'] = ADD_F,
                                          ['='] = EQ_F,
                                          ['^'] = POW_F,
                                          ['x'] = X_F,
                                          ['e'] = E_F};

    printf(BLUE_C);
    disable_line_break();

    for (int i = 0; i < files_length; i++)
    {
        for (int j = 0; j < s[j]; j++)
        {
            const char *file = NULL;
            file = file_names[(int)s[j]];
            if (file)
            {
                if (!print_n_file_string(file, i, 0))
                {
                    printf("%sFile erorr!\n%s", RED_C, RESET_C);
                    free(s);
                    return;
                }
                putchar(' ');
            }
        }
        printf("\n");
    }
    enable_line_break();
    printf(RESET_C);

    free(s);
}

void process_roots_with_pretty_print(struct QuadraticEquation *equation)
{
    my_assert(equation);

    print_and_say_phrase(THINKING_S);
    loading();
    print_and_say_phrase(SOLVED_S);
    printf("\n");
    if (ARGS.ascii_arts)
        print_equation_in_ascii_art(equation);
    printf("\n");
    print_answer_table(equation);
    printf("\n");
    if (ARGS.graph)
        draw_quadratic_equation_graph(equation);
    printf("\n");
}
