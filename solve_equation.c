#include <math.h>
#include <stddef.h>
#include <assert.h>
#include "solve_equation.h"

int solve_linear_equation(float b, float c, float *px)
{
    assert(isfinite(b));
    assert(isfinite(c));
    assert(px != NULL);

    if (b == 0.f)
        return (c == 0.f) ? INFINITY_ROOTS : 0;
    *px = -c / b;
    return 1;
}

int solve_quadratic_equation(float a, float b, float c, float *px1, float *px2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(px1 != NULL);
    assert(px2 != NULL);
    assert(px1 != px2);

    if (a == 0.f)
        return solve_linear_equation(b, c, px1);

    float D = b * b - 4 * a * c;
    if (D > 0)
    {
        *px1 = (-b - sqrt(D)) / (2 * a);
        *px2 = (-b + sqrt(D)) / (2 * a);
        return 2;
    }
    else if (D == 0.f)
    {
        *px1 = -b / (2 * a);
        return 1;
    }
    return 0;
}
