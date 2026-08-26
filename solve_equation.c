#include "solve_equation.h"
#include <math.h>
#include <stddef.h>
#include "my_assert.h"
#include "config.h"

enum RootsCount solve_linear_equation(struct QuadraticEquation *equation)
{
    my_assert(equation);
    my_assert(isfinite(equation->b));
    my_assert(isfinite(equation->c));

    if (d_is_equal(equation->b, 0.))
    {
        equation->n_roots = (d_is_equal(equation->c, 0.)) ? INFINITY_ROOTS : NO_REAL_ROOTS;
    }
    else
    {
        equation->x1 = equation->x2 = -equation->c / equation->b;
        equation->n_roots = ONE_REAL_ROOT;
    }
    return equation->n_roots;
}

enum RootsCount solve_quadratic_equation(struct QuadraticEquation *equation)
{
    my_assert(equation);
    my_assert(isfinite(equation->a));
    my_assert(isfinite(equation->b));
    my_assert(isfinite(equation->c));

    if (d_is_equal(equation->a, 0.))
        return solve_linear_equation(equation);

    double D = equation->b * equation->b - 4 * equation->a * equation->c;
    if (d_is_equal(D, 0.))
    {
        equation->x1 = equation->x2 = -equation->b / (2 * equation->a);
        equation->n_roots = ONE_REAL_ROOT;
    }
    else if (D > 0.)
    {
        equation->x1 = (-equation->b - sqrt(D)) / (2 * equation->a);
        equation->x2 = (-equation->b + sqrt(D)) / (2 * equation->a);
        equation->n_roots = TWO_REAL_ROOTS;
    }
    else
    {
        equation->n_roots = NO_REAL_ROOTS;
    }
    return equation->n_roots;
}

int is_equal(double a, double b)
{
    return fabs(a - b) <= EPSILON;
}

void print_equation(struct QuadraticEquation *equation)
{
    my_assert(equation);

    printf("Equation: .a = %lg, .b = %lg, .c = %lg\n", equation->a, equation->b, equation->c);
}