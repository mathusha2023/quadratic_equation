#include "solve_equation.h"

const int X_AXIS_LEN = 80;   ///< Length of x-axis in characters
const int Y_AXIS_LEN = 40;   ///< Length of y-axis in characters
const double BASE_SCALE = 1; ///< Default scale if it will be 0

/**
 * @brief Point struct
 *
 */
struct Point
{
    double x, y;
};

/**
 * @brief Draw quadratic equation graph
 *
 * This function will draw quadratic equation graph.
 * If a != 0 then it will draw parabola, if a = 0 then it will draw line
 *
 * @param equation
 */
void draw_quadratic_equation_graph(struct QuadraticEquation *equation);
