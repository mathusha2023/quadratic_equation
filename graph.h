#ifndef GRAPH_H
#define GRAPH_H

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
 * @brief Calculate f(x) = ax^2 + bx + c
 *
 * This function calculate the functions f(x) = ax^2 + bx + c
 * in point x
 *
 * @param x
 * @param equation
 * @return double function value at point x
 */
double f(double x, struct QuadraticEquation *equation);

/**
 * @brief Get the scale of axis using key point and axis length
 *
 * @param point
 * @param axis_len
 * @return double
 */
double get_scale(double point, int axis_len);

/**
 * @brief Draw quadratic equation graph
 *
 * This function will draw quadratic equation graph.
 * If a != 0 then it will draw parabola, if a = 0 then it will draw line
 *
 * @param equation
 */
void draw_quadratic_equation_graph(struct QuadraticEquation *equation);

#endif // GRAPH_H