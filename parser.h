#include "solve_equation.h"

struct Parser
{
    char *s;
    int is_correct_format;
    int (*parse)(struct Parser *parser, struct QuadraticEquation *equation);
};

struct Parser init_parser(char *s);
