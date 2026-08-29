#ifndef SOLVE_EQUATION_H

#define SOLVE_EQUATION_H

/**
 * @brief Count of roots enum
 *
 */
enum RootsCount
{
    INFINITY_ROOTS = -1,
    NO_REAL_ROOTS = 0,
    ONE_REAL_ROOT = 1,
    TWO_REAL_ROOTS = 2
};

/**
 * @brief Quadratic equation struct
 *
 * Struct for saving quadratic equation in useful form
 *
 */
struct QuadraticEquation
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    enum RootsCount n_roots;
};

/**
 * @brief Check if a and b are equal
 *
 * This function checks if a and b are equal with epsilon
 * because comparing two double numbers is hard
 *
 * @param a
 * @param b
 * @return int 1 if equal else 0
 */
int is_equal(double a, double b);

/**
 * @brief Debug print quadratic equation
 *
 * @param equation
 */
void print_equation(struct QuadraticEquation *equation);

/**
 * @brief Solve quadratic equation
 *
 * This function get equation with coeffs and solve it with changing another
 * struct fields
 *
 * @param equation
 * @return enum RootsCount
 */
enum RootsCount solve_quadratic_equation(struct QuadraticEquation *equation);

/**
 * @brief Solve linear equation
 *
 * This function get equation with coeffs and solve it with changing another
 * struct fields
 *
 * @warning This function works only if a = 0
 *
 * @param equation
 * @return enum RootsCount
 */
enum RootsCount solve_linear_equation(struct QuadraticEquation *equation);

#endif // SOLVE_EQUATION_H