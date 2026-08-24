// Deprecated Parser tests

#include "solve_equation.h"

struct ParserTestCase
{
    int num;
    const char *s;
    int is_correct_format;
    int is_correct_parse;
    struct QuadraticEquation equation;
};

int run_parser_tests(void);