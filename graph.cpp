#include "graph.h"
#include <math.h>
#include "solve_equation.h"
#include "my_assert.h"
#include "config.h"

/**
 * @brief Check if a and b are equal on graph (+- 10% to scale of b)
 *
 * @param a
 * @param b
 * @param scale_b
 * @return int 1 if equal else 0
 */
static int is_equal_on_graph(double a, double b, double scale_b)
{
    double scale_k = 0.1;
    return b - scale_b * scale_k < a && a < b + scale_b * scale_k;
}

/**
 * @brief Normilize equation
 *
 * This function normilize equation (set leadig coefficient to 1 or -1)
 *
 * @param equation
 */
static void normilize_equation(struct QuadraticEquation *equation)
{
    my_assert(equation);

    if (!d_is_equal(equation->a, 0))
    {
        equation->b /= fabs(equation->a);
        equation->c /= fabs(equation->a);
        equation->a /= fabs(equation->a);
    }
    else
    {
        if (!d_is_equal(equation->b, 0))
        {
            equation->c /= fabs(equation->b);
            equation->b /= fabs(equation->b);
        }
        else
        {
            if (!d_is_equal(equation->c, 0))
                equation->c /= fabs(equation->c);
        }
    }
}

/**
 * @brief Draw quadratic equation graph using scale
 *
 * @param x_scale
 * @param y_scale
 * @param equation
 */
static void draw_graph(double x_scale, double y_scale, struct QuadraticEquation *equation)
{
    int x = 0, y = 0;

    for (y = Y_AXIS_LEN / 2; y > -(Y_AXIS_LEN / 2); y--)
    {
        for (x = -(X_AXIS_LEN / 2); x < X_AXIS_LEN / 2; x++)
        {
            if (y == Y_AXIS_LEN / 2 && x == -1)
                putchar('y');
            else if (y == 0 && x == X_AXIS_LEN / 2 - 1)
                putchar('x');
            else if (y == Y_AXIS_LEN / 2 && x == 0)
                putchar('^');
            else if (y == 0 && x == X_AXIS_LEN / 2 - 2)
                putchar('>');
            else if (is_equal_on_graph(f(x * x_scale, equation), y * y_scale, y_scale))
            {
                printf(GREEN_C);
                putchar('*');
                printf(RESET_C);
            }
            else if (x == 0 && y == 0)
                putchar('+');
            else if (y == 0)
                putchar('-');
            else if (x == 0)
                putchar('|');
            else
                putchar(' ');
        }
        putchar('\n');
    }
}

/**
 * @brief Draw horizontal line y = c
 *
 * @warning This function will not work if a != 0 or b != 0
 *
 * @param equation
 */
static void draw_horizontal_line(struct QuadraticEquation *equation)
{
    my_assert(equation);
    my_assert(d_is_equal(equation->a, 0)); // a = 0
    my_assert(d_is_equal(equation->b, 0)); // b = 0

    double y_scale = get_scale(equation->c, Y_AXIS_LEN);
    double x_scale = 1;
    draw_graph(x_scale, y_scale, equation);
}

/**
 * @brief Draw line y = bx + c
 *
 * @warning This function will not work if a != 0
 *
 * @param equation
 */
static void draw_line(struct QuadraticEquation *equation)
{
    my_assert(equation);
    my_assert(d_is_equal(equation->a, 0)); // a = 0

    if (d_is_equal(equation->b, 0))
        return draw_horizontal_line(equation);

    // b != 0
    struct Point x_zero_p = {.x = 0, .y = equation->c};
    struct Point y_zero_p = {.x = -equation->c / equation->b, .y = 0};

    double x_scale = get_scale(y_zero_p.x, X_AXIS_LEN);
    double y_scale = get_scale(x_zero_p.y, Y_AXIS_LEN);

    draw_graph(x_scale, y_scale, equation);
}

/**
 * @brief Draw parabola y = ax^2 + bx + c
 *
 * @warning This function will not work if a = 0
 *
 * @param equation
 */
static void draw_parabola(struct QuadraticEquation *equation)
{
    my_assert(equation);
    my_assert(!d_is_equal(equation->a, 0)); // a != 0

    double vertex_x = -equation->b / (2 * equation->a);
    struct Point vertex = {.x = vertex_x, .y = f(vertex_x, equation)};

    double x_scale = get_scale(vertex.x, X_AXIS_LEN);
    double y_scale = get_scale(vertex.y, Y_AXIS_LEN);

    draw_graph(x_scale, y_scale, equation);
}

double f(double x, struct QuadraticEquation *equation)
{
    my_assert(equation);

    return equation->a * x * x + equation->b * x + equation->c;
}

double get_scale(double point, int axis_len)
{
    int scale_factor = 4;

    if (!d_is_equal(point, 0))
        return fabs(point * scale_factor / axis_len);
    return BASE_SCALE;
}

void draw_quadratic_equation_graph(struct QuadraticEquation *equation)
{
    my_assert(equation);
    normilize_equation(equation);

    if (!d_is_equal(equation->a, 0))
        return draw_parabola(equation);
    return draw_line(equation);
}