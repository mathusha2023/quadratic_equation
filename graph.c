#include "graph.h"
#include <math.h>
#include "solve_equation.h"
#include "my_assert.h"
#include "config.h"

static double max(double a, double b)
{
    return a > b ? a : b;
}

static double f(double x, struct QuadraticEquation *equation)
{
    my_assert(equation);

    return equation->a * x * x + equation->b * x + equation->c;
}

static int is_equal_on_graph(double a, double b, double scale_b)
{
    return b - scale_b / 4 < a && a < b + scale_b / 4;
}

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

static double get_scale(double point, int axis_len)
{
    int scale_factor = 8;
    return max(fabs(point * scale_factor / axis_len), MIN_SCALE);
}

static void draw_horizontal_line(struct QuadraticEquation *equation)
{
    my_assert(equation);
    my_assert(d_is_equal(equation->a, 0)); // a = 0
    my_assert(d_is_equal(equation->b, 0)); // b = 0

    double y_scale = get_scale(equation->c, Y_AXIS_LEN);
    double x_scale = 1;
    draw_graph(x_scale, y_scale, equation);
}

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

void draw_quadratic_equation_graph(struct QuadraticEquation *equation)
{
    my_assert(equation);

    if (!d_is_equal(equation->a, 0))
        return draw_parabola(equation);
    return draw_line(equation);
}