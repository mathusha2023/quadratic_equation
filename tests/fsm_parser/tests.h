#include "solve_equation.h"

/// @brief Parser test case object
struct FSMParserTestCase
{
    int num;
    const char *s;
    int error_index;
    struct QuadraticEquation equation;
};

/**
 * @brief Run parser testing
 *
 * @return int 1 if all tests passed else 0
 */
int run_fsm_parser_tests(void);