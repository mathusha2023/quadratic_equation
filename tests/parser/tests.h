#include "solve_equation.h"

struct ParserTestCase
{
    int num;
    char *s;
    int is_correct_format;
    int is_correct_parse;
    struct QuadraticEquation equation;
};

int run_parser_tests(void);