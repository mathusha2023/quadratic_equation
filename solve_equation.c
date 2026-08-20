#include <math.h>
#include <stddef.h>
#include <assert.h>
#include "solve_equation.h"
#include "config.h"

enum roots_count solve_linear_equation(float b, float c, float *px)
{
    assert(isfinite(b));
    assert(isfinite(c));
    assert(px != NULL);

    if (d_is_equal(b, 0.f))
        return (d_is_equal(c, 0.f)) ? INFINITY_ROOTS : NO_REAL_ROOTS;
    *px = -c / b;
    return ONE_REAL_ROOT;
}

enum roots_count solve_quadratic_equation(float a, float b, float c, float *px1, float *px2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(px1 != NULL);
    assert(px2 != NULL);
    assert(px1 != px2);

    if (d_is_equal(a, 0.f))
        return solve_linear_equation(b, c, px1);

    float D = b * b - 4 * a * c;
    if (D > 0)
    {
        *px1 = (-b - sqrt(D)) / (2 * a);
        *px2 = (-b + sqrt(D)) / (2 * a);
        return TWO_REAL_ROOTS;
    }
    else if (d_is_equal(D, 0.f))
    {
        *px1 = -b / (2 * a);
        return ONE_REAL_ROOT;
    }
    return NO_REAL_ROOTS;
}

int is_equal(float a, float b)
{
    return abs(a - b) <= EPSILON;
}