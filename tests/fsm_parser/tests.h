#include "solve_equation.h"

struct FSMParserTestCase
{
    int num;
    const char *s;
    int error_index;
    struct QuadraticEquation equation;
};

int run_fsm_parser_tests(void);