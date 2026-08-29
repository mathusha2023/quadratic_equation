#include "solve_equation.h"

/// @brief Quadratic equation solver test case object
struct EquationTestCase
{
    int num;
    struct QuadraticEquation equation;
};

/**
 * @brief Run equation solver testing
 *
 * @return int 1 if all tests passed else 0
 */
int run_equation_tests(void);