#ifndef SOLVE_EQUATION_H

#define SOLVE_EQUATION_H

enum RootsCount
{
    INFINITY_ROOTS = -1,
    NO_REAL_ROOTS = 0,
    ONE_REAL_ROOT = 1,
    TWO_REAL_ROOTS = 2
};

struct QuadraticEquation
{
    float a;
    float b;
    float c;
    float x1;
    float x2;
    enum RootsCount n_roots;
};

int is_equal(float a, float b);
enum RootsCount solve_quadratic_equation(struct QuadraticEquation *equation);
enum RootsCount solve_linear_equation(struct QuadraticEquation *equation);

#endif // SOLVE_EQUATION_H