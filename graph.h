#include "solve_equation.h"

const int X_AXIS_LEN = 80;
const int Y_AXIS_LEN = 40;
const double BASE_SCALE = 1;

struct Point
{
    double x, y;
};

void draw_quadratic_equation_graph(struct QuadraticEquation *equation);
