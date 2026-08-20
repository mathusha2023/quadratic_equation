#include <math.h>
#include <stddef.h>
#include <assert.h>
#include "solve_equation.h"
#include "config.h"

enum RootsCount solve_linear_equation(struct QuadraticEquation *equation)
{
    assert(equation != NULL);
    assert(isfinite(equation->b));
    assert(isfinite(equation->c));

    if (d_is_equal(equation->b, 0.f))
    {
        equation->n_roots = (d_is_equal(equation->c, 0.f)) ? INFINITY_ROOTS : NO_REAL_ROOTS;
    }
    else
    {
        equation->x1 = -equation->c / equation->b;
        equation->n_roots = ONE_REAL_ROOT;
    }
    return equation->n_roots;
}

enum RootsCount solve_QuadraticEquation(struct QuadraticEquation *equation)
{
    assert(equation != NULL);
    assert(isfinite(equation->a));
    assert(isfinite(equation->b));
    assert(isfinite(equation->c));

    if (d_is_equal(equation->a, 0.f))
        return solve_linear_equation(equation);

    float D = equation->b * equation->b - 4 * equation->a * equation->c;
    if (D > 0)
    {
        equation->x1 = (-equation->b - sqrt(D)) / (2 * equation->a);
        equation->x2 = (-equation->b + sqrt(D)) / (2 * equation->a);
        equation->n_roots = TWO_REAL_ROOTS;
    }
    else if (d_is_equal(D, 0.f))
    {
        equation->x1 = -equation->b / (2 * equation->a);
        equation->n_roots = ONE_REAL_ROOT;
    }
    else
    {
        equation->n_roots = NO_REAL_ROOTS;
    }
    return equation->n_roots;
}

int is_equal(float a, float b)
{
    return abs(a - b) <= EPSILON;
}